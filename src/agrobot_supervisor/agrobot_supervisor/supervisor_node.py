#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
supervisor_node.py — Agrobot TOM v2 discrete step-and-shoot picking supervisor.

SCOPE (tonight): capture-only. The supervisor steps the rail, settles, captures
one perception snapshot per stop, builds a pick queue, and loops until the rail
clamps (end of travel). Arm picking is STUBBED — picks are logged to a queue,
not executed.

WHAT THIS NODE OWNS:
  - The state machine that sequences the run.
  - The step-size math (from camera Z + intrinsics).
  - Per-stop deduplication of tomatoes by persistent_id.
WHAT IT DOES NOT OWN:
  - Any hardware. It calls /rail_mover/goto (a service) and reads perception
    topics. It commands; it does not actuate.

STATE MACHINE:
  IDLE -> STEP -> SETTLE -> CAPTURE -> PROCESS_QUEUE -> (loop to STEP)
                                                    -> END_REACHED -> RETURN -> DONE

  STEP          : async call /rail_mover/goto with target = current_j0 + step.
  SETTLE        : fixed dwell so the cart is mechanically still AND tomato_spatial
                  has a fresh point cloud before we trust a capture.
  CAPTURE       : take exactly ONE /agrobot/tomato_tracks snapshot (Option A —
                  the free-running pipeline is sampled once, not gated).
  PROCESS_QUEUE : parse the snapshot, dedup by persistent_id, enqueue new tomatoes.
  END_REACHED   : the rail service reported clamped=True -> rail is at end of travel.
  RETURN        : send the rail back to the start coordinate.

PERCEPTION INTERFACE (confirmed from live messages):
  /agrobot/tomato_tracks : std_msgs/String, JSON list of track objects. Each:
      { "persistent_id": int, "tomato_id": int,
        "centroid": {"x": float, "y": float, "z": float},
        "sphere": {...}, "confidence": float,
        "clipped_image": "<base64 jpeg>", "age": int, "smoothed": bool }
  All track-field key paths are isolated in _parse_track() below — if the
  perception schema changes, that one function is the only edit point.
"""

import json
import math
from enum import Enum, auto

import rclpy
from rclpy.node import Node
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor

from std_msgs.msg import String
from sensor_msgs.msg import CameraInfo

from agrobot_motion.srv import RailGoTo
from agrobot_motion.srv import AnthroGoTo

import math

CELEBRATION_POSES_DEG = {
    "P1":     [ 35, -20,   0, -90, -70],
    "P2":     [ 35, -45,  40, -90, -70],
    "P3":     [-35, -20,   0, -90, -70],
    "P4":     [-35, -45,  40, -90, -70],
    "CROUCH": [  0, -15,  60,  90,  45],
}

CELEBRATION_SEQUENCE = ["P1", "P2", "P1", "P3", "P4", "P3", "CROUCH"]

# --------------------------------------------------------------------------
# Track parsing — SINGLE SOURCE OF TRUTH for the tomato_tracks JSON schema.
# If perception changes the JSON keys, edit ONLY this function.
# --------------------------------------------------------------------------
def _parse_track(track: dict) -> dict:
    """Extract the fields the supervisor cares about from one raw track dict.

    Returns a flat dict, or None if the track is missing required fields.
    """
    try:
        centroid = track["centroid"]
        return {
            "persistent_id": int(track["persistent_id"]),
            "x": float(centroid["x"]),
            "y": float(centroid["y"]),
            "z": float(centroid["z"]),
            "confidence": float(track.get("confidence", 0.0)),
            "age": int(track.get("age", 0)),
        }
    except (KeyError, TypeError, ValueError):
        return None


class State(Enum):
    IDLE = auto()
    STEP = auto()
    SETTLE = auto()
    CAPTURE = auto()
    PROCESS_QUEUE = auto()
    END_REACHED = auto()
    RETURN = auto()
    DONE = auto()


class SupervisorNode(Node):

    def __init__(self):
        super().__init__("agrobot_supervisor")

        # --- Parameters (all tunable at launch, no recompile) ---
        # Rail geometry. The rail service clamps to [0.05, 1.30]; we keep our
        # own copy of the start so RETURN knows where "home" is.
        self.start_position = self.declare_parameter(
            "start_position", 0.05).value
        # Step-size fallback (m) used until camera intrinsics + a Z estimate
        # are available. Also a hard floor so we never request a zero step.
        self.fallback_step = self.declare_parameter(
            "fallback_step", 0.15).value
        self.min_step = self.declare_parameter("min_step", 0.05).value
        self.max_step = self.declare_parameter("max_step", 0.40).value
        # Fraction of frame width to advance per step (0.8 => 20% overlap).
        self.overlap_factor = self.declare_parameter(
            "overlap_factor", 0.8).value
        # SETTLE dwell (s): cart mechanically still + fresh point cloud.
        self.settle_seconds = self.declare_parameter(
            "settle_seconds", 1.0).value
        # How long to wait for a fresh tracks message during CAPTURE (s).
        self.capture_timeout = self.declare_parameter(
            "capture_timeout", 3.0).value
        # Minimum age (frames) for a track to count — rejects one-frame noise.
        self.min_track_age = self.declare_parameter("min_track_age", 2).value
        # Minimum detection confidence for a track to be enqueued.
        self.min_confidence = self.declare_parameter(
            "min_confidence", 0.30).value

        # --- ROS interfaces ---
        cb = ReentrantCallbackGroup()

        self.rail_client = self.create_client(
            RailGoTo, "/rail_mover/goto", callback_group=cb)

        self.anthro_client = self.create_client(
            AnthroGoTo, "/anthro_mover/goto", callback_group=cb)

        self.tracks_sub = self.create_subscription(
            String, "/agrobot/tomato_tracks",
            self._tracks_cb, 10, callback_group=cb)

        self.caminfo_sub = self.create_subscription(
            CameraInfo, "/camera/camera/color/camera_info",
            self._caminfo_cb, 10, callback_group=cb)

        # --- Runtime state ---
        self.state = State.IDLE
        self.current_j0 = self.start_position   # last known rail position
        self.fx = None                          # camera focal length x (px)
        self.image_width = None                 # camera width (px)
        self.latest_tracks_json = None          # most recent raw msg.data
        self.latest_tracks_stamp = None         # rclpy time of that msg
        self.logged_raw_once = False            # log raw JSON on first receipt

        # Pick queue: persistent_id -> tomato dict. A dict keyed by
        # persistent_id IS the dedup mechanism — re-seeing the same tomato at
        # a later station just overwrites its entry, never double-queues it.
        self.pick_queue = {}

        self.station_index = 0
        self._rail_call_in_flight = False
        self._settle_deadline = None
        self._capture_deadline = None
        self._capture_started_stamp = None

        # Main tick — drives the state machine at 10 Hz.
        self.timer = self.create_timer(0.1, self._tick, callback_group=cb)

        self.get_logger().info(
            "agrobot_supervisor started. Waiting for /rail_mover/goto service "
            "and camera_info before stepping.")

    # ----------------------------------------------------------------------
    # Subscriptions
    # ----------------------------------------------------------------------
    def _caminfo_cb(self, msg: CameraInfo):
        """Cache focal length and width once — needed for step-size math."""
        if self.fx is None:
            # CameraInfo.k is the 3x3 intrinsic matrix, row-major: k[0] = fx.
            self.fx = msg.k[0]
            self.image_width = msg.width
            self.get_logger().info(
                f"Camera intrinsics cached: fx={self.fx:.1f} "
                f"width={self.image_width}px")

    def _tracks_cb(self, msg: String):
        """Store the most recent tracks message. CAPTURE samples this once."""
        self.latest_tracks_json = msg.data
        self.latest_tracks_stamp = self.get_clock().now()
        if not self.logged_raw_once:
            # Log the raw JSON ONCE so the real schema is visible in the
            # supervisor's own output — sanity-check against _parse_track().
            self.logged_raw_once = True
            preview = msg.data[:300]
            self.get_logger().info(
                f"First tomato_tracks message received. Raw JSON preview: "
                f"{preview}")

    # ----------------------------------------------------------------------
    # Step-size math
    # ----------------------------------------------------------------------
    def _compute_step(self, wall_z: float) -> float:
        """Compute the rail step (m) for ~overlap_factor frame coverage.

        Horizontal FOV from intrinsics: theta = 2*atan((width/2)/fx).
        Frame width on the wall plane at distance Z: W = 2*Z*tan(theta/2).
        Step = overlap_factor * W  (overlap_factor < 1 => frames overlap).
        Clamped to [min_step, max_step].
        """
        if self.fx is None or self.image_width is None or wall_z <= 0.0:
            return self.fallback_step
        half_fov = math.atan((self.image_width / 2.0) / self.fx)
        frame_width = 2.0 * wall_z * math.tan(half_fov)
        step = self.overlap_factor * frame_width
        return max(self.min_step, min(self.max_step, step))

    def _estimate_wall_z(self, tomatoes: list) -> float:
        """Estimate working-plane distance Z from the captured tomatoes.

        Tonight's simple version: median tomato centroid Z. (The histogram-
        mode-of-depth-band method is the planned upgrade — it needs the raw
        depth image; median of detected tomatoes is a fine first pass and
        needs nothing but the snapshot we already have.)
        Returns 0.0 if there is nothing to estimate from -> fallback step.
        """
        zs = sorted(t["z"] for t in tomatoes)
        if not zs:
            return 0.0
        mid = len(zs) // 2
        if len(zs) % 2:
            return zs[mid]
        return 0.5 * (zs[mid - 1] + zs[mid])

    # ----------------------------------------------------------------------
    # State machine tick
    # ----------------------------------------------------------------------
    def _tick(self):
        handler = {
            State.IDLE: self._do_idle,
            State.STEP: self._do_step,
            State.SETTLE: self._do_settle,
            State.CAPTURE: self._do_capture,
            State.PROCESS_QUEUE: self._do_process_queue,
            State.END_REACHED: self._do_end_reached,
            State.RETURN: self._do_return,
            State.DONE: self._do_done,
        }.get(self.state)
        if handler is not None:
            handler()

    def _transition(self, new_state: State):
        self.get_logger().info(
            f"[state] {self.state.name} -> {new_state.name}")
        self.state = new_state

    # --- IDLE: wait for dependencies, then begin -------------------------
    def _do_idle(self):
        if not self.rail_client.service_is_ready():
            # service_is_ready is non-blocking; just keep waiting.
            return
        self.get_logger().info(
            "Rail service available. Beginning step-and-shoot run.")
        self._transition(State.STEP)

    # --- STEP: command the rail one step forward -------------------------
    def _do_step(self):
        if self._rail_call_in_flight:
            return  # already moving; wait for the result callback

        # Use the last captured tomatoes (if any) to size this step.
        captured = list(self.pick_queue.values())
        wall_z = self._estimate_wall_z(captured)
        step = self._compute_step(wall_z)
        target = self.current_j0 + step

        self.get_logger().info(
            f"[STEP] station {self.station_index}: j0 {self.current_j0:.3f} "
            f"-> {target:.3f} (step={step:.3f}m, wall_z="
            f"{wall_z:.3f}m)")

        req = RailGoTo.Request()
        req.target_position = target
        self._rail_call_in_flight = True
        future = self.rail_client.call_async(req)
        future.add_done_callback(self._rail_step_done)

    def _rail_step_done(self, future):
        """Result of a STEP rail move. Runs in an executor thread."""
        self._rail_call_in_flight = False
        try:
            res = future.result()
        except Exception as exc:  # noqa: BLE001
            self.get_logger().error(f"[STEP] rail service call failed: {exc}")
            self._transition(State.DONE)
            return

        self.current_j0 = res.final_position
        self.get_logger().info(
            f"[STEP] rail result: success={res.success} "
            f"clamped={res.clamped} final={res.final_position:.3f}")

        if not res.success:
            self.get_logger().error(
                f"[STEP] rail move failed: {res.message}. Ending run.")
            self._transition(State.DONE)
            return

        if res.clamped:
            # The rail truncated our target -> we are at end of travel.
            # This is the natural search terminator.
            self.get_logger().info(
                "[STEP] rail clamped -> end of travel reached.")
            self._transition(State.END_REACHED)
            return

        # Normal move complete -> let the cart settle before capturing.
        self._settle_deadline = self.get_clock().now() + rclpy.duration.Duration(
            seconds=self.settle_seconds)
        self._transition(State.SETTLE)

    # --- SETTLE: fixed dwell so cart is still + point cloud is fresh -----
    def _do_settle(self):
        if self.get_clock().now() >= self._settle_deadline:
            # Mark the moment capture begins; CAPTURE only accepts a tracks
            # message published AFTER this stamp (guarantees a fresh frame).
            self._capture_started_stamp = self.get_clock().now()
            self._capture_deadline = self.get_clock().now() + \
                rclpy.duration.Duration(seconds=self.capture_timeout)
            self._transition(State.CAPTURE)

    # --- CAPTURE: take exactly ONE fresh tracks snapshot -----------------
    def _do_capture(self):
        # Accept the latest tracks message only if it arrived AFTER settle
        # finished — otherwise it may describe a pre-move / mid-move frame.
        have_fresh = (
            self.latest_tracks_stamp is not None
            and self._capture_started_stamp is not None
            and self.latest_tracks_stamp > self._capture_started_stamp
        )
        if have_fresh:
            self._captured_json = self.latest_tracks_json
            self.get_logger().info(
                f"[CAPTURE] station {self.station_index}: fresh snapshot taken.")
            self._transition(State.PROCESS_QUEUE)
            return

        if self.get_clock().now() >= self._capture_deadline:
            # No fresh message in time — treat as an empty capture and move on
            # rather than stalling the whole run.
            self.get_logger().warn(
                f"[CAPTURE] station {self.station_index}: no fresh tracks "
                f"within {self.capture_timeout:.1f}s — treating as empty.")
            self._captured_json = "[]"
            self._transition(State.PROCESS_QUEUE)

    # --- PROCESS_QUEUE: parse snapshot, dedup, enqueue -------------------
    def _do_process_queue(self):
        raw = getattr(self, "_captured_json", "[]")
        try:
            tracks = json.loads(raw)
            if not isinstance(tracks, list):
                raise ValueError("tomato_tracks payload is not a JSON list")
        except (json.JSONDecodeError, ValueError) as exc:
            self.get_logger().error(
                f"[PROCESS] could not parse tracks JSON: {exc}")
            tracks = []

        new_count = 0
        for raw_track in tracks:
            parsed = _parse_track(raw_track)
            if parsed is None:
                self.get_logger().warn(
                    "[PROCESS] skipping malformed track entry.")
                continue
            # Quality gates: reject young/noisy tracks.
            if parsed["age"] < self.min_track_age:
                continue
            if parsed["confidence"] < self.min_confidence:
                continue

            pid = parsed["persistent_id"]
            if pid not in self.pick_queue:
                new_count += 1
                self.get_logger().info(
                    f"[QUEUE] + tomato persistent_id={pid} "
                    f"at ({parsed['x']:.3f}, {parsed['y']:.3f}, "
                    f"{parsed['z']:.3f}) conf={parsed['confidence']:.2f}")
            # Keyed by persistent_id => re-seeing a tomato just refreshes it,
            # never double-queues. This IS the dedup.
            parsed["station_seen"] = self.station_index
            self.pick_queue[pid] = parsed

        self.get_logger().info(
            f"[PROCESS] station {self.station_index}: {len(tracks)} tracks in "
            f"snapshot, {new_count} new, queue total={len(self.pick_queue)}")

        # ---- PICK IS STUBBED HERE ----
        # Tonight: picking is not executed. The arm-pick service call will go
        # in this spot in a future revision. For now the queue is the
        # deliverable; new entries above are the "would pick" log.

        self.station_index += 1
        self._transition(State.STEP)

    # --- END_REACHED: rail is at end of travel ---------------------------
    def _do_end_reached(self):
        if getattr(self, "_celebration_started", False):
            return                       # guard: timer re-entry — already running
        self._celebration_started = True
    
        self.get_logger().info(
            f"=== END OF RAIL REACHED ===  stations visited="
            f"{self.station_index}  tomatoes queued={len(self.pick_queue)}")
        for pid, t in sorted(self.pick_queue.items()):
            self.get_logger().info(
                f"  queued tomato persistent_id={pid}: "
                f"({t['x']:.3f}, {t['y']:.3f}, {t['z']:.3f}) "
                f"conf={t['confidence']:.2f}")
    
        self.celebrate()                  # now runs exactly ONCE
        self._transition(State.RETURN)

    # --- RETURN: send the rail home --------------------------------------
    def _do_return(self):
        if self._rail_call_in_flight:
            return
        self.get_logger().info(
            f"[RETURN] sending rail back to start ({self.start_position:.3f}).")
        req = RailGoTo.Request()
        req.target_position = self.start_position
        self._rail_call_in_flight = True
        future = self.rail_client.call_async(req)
        future.add_done_callback(self._rail_return_done)

    def _rail_return_done(self, future):
        self._rail_call_in_flight = False
        try:
            res = future.result()
            self.current_j0 = res.final_position
            self.get_logger().info(
                f"[RETURN] rail home: success={res.success} "
                f"final={res.final_position:.3f}")
        except Exception as exc:  # noqa: BLE001
            self.get_logger().error(f"[RETURN] rail call failed: {exc}")
        self._transition(State.DONE)

    # --- DONE: terminal --------------------------------------------------
    def _do_done(self):
        # One-shot log, then the timer keeps ticking harmlessly in DONE.
        if not getattr(self, "_done_logged", False):
            self._done_logged = True
            self.get_logger().info(
                f"=== RUN COMPLETE ===  total tomatoes in pick queue: "
                f"{len(self.pick_queue)}. Supervisor idle.")

    def _send_anthro_pose(self, pose_deg, label):
      """Send one anthro joint pose (degrees) and BLOCK until it completes.
   
      Returns True on success, False on any failure. The celebration is a
      fixed scripted sequence, so a simple blocking call per pose is correct
      here — unlike the rail STEP, there is nothing else the supervisor needs
      to do concurrently while celebrating.
      """
      if not self.anthro_client.service_is_ready():
          self.get_logger().error(
              "[CELEBRATE] /anthro_mover/goto not available — skipping emote.")
          return False
   
      req = AnthroGoTo.Request()
      req.joint_positions = [math.radians(d) for d in pose_deg]
      req.velocity_scaling = 0.5          # celebration: fast, no precision needed
   
      self.get_logger().info(f"[CELEBRATE] -> pose '{label}' {pose_deg} deg")
      future = self.anthro_client.call_async(req)
   
      # Block this thread until the result arrives. Safe because the node runs
      # on a MultiThreadedExecutor — other callbacks keep spinning.
      while rclpy.ok() and not future.done():
          pass
      try:
          res = future.result()
      except Exception as exc:  # noqa: BLE001
          self.get_logger().error(f"[CELEBRATE] pose '{label}' call failed: {exc}")
          return False
   
      if not res.success:
          self.get_logger().warn(
              f"[CELEBRATE] pose '{label}' did not succeed: {res.message}")
          return False
      return True
 
 
    def celebrate(self):
        """Run the end-of-rail celebration emote.
     
        Walks CELEBRATION_SEQUENCE through the anthro group. A failed pose is
        logged and the sequence continues — a celebration should never be able
        to abort the run.
        """
        self.get_logger().info("=== CELEBRATION: end of rail reached! ===")
        for label in CELEBRATION_SEQUENCE:
            pose = CELEBRATION_POSES_DEG.get(label)
            if pose is None:
                self.get_logger().warn(
                    f"[CELEBRATE] unknown pose label '{label}' — skipping.")
                continue
            self._send_anthro_pose(pose, label)
        self.get_logger().info("=== CELEBRATION complete. ===")

def main(args=None):
    rclpy.init(args=args)
    node = SupervisorNode()
    # MultiThreadedExecutor: the rail service-call result callbacks and the
    # state-machine timer must be able to run concurrently. With a single
    # thread the call_async result future cannot resolve while the timer
    # callback is on the stack.
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
