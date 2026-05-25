#!/usr/bin/env python3
"""Per-joint ROS 2 bridge node for Copley APV/APZ CANopen drives.

Mirrors the wire protocol of epos2_j3_bridge so the existing
epos2_arm_controller orchestrator can drive a mixed-vendor arm without
caring which drive is behind a given joint:

  Services:
    /copley/jN/clear_fault          (std_srvs/Trigger)
    /copley/jN/arm_ipm              (std_srvs/Trigger)
    /copley/jN/disarm_ipm           (std_srvs/Trigger)
    /copley/jN/move_absolute_timed  (epos2_bridge_interfaces/MoveAbsoluteTimed)

  Subscriptions:
    /copley/jN/reduced_traj         (Float64MultiArray, [q,v,dt,...])

  Publications:
    /joint_states                   (sensor_msgs/JointState)
    /copley/jN/fault                (std_msgs/Bool)

  Action server:
    /jN_position_controller/follow_joint_trajectory  (control_msgs/FollowJointTrajectory)

Internally, the bridge:
  1. Uses canopen_interfaces SDO services for setup, fault clear, mode
     selection, and PDO mapping verification.
  2. Uses raw SocketCAN for runtime PDO TX/RX (RPDO1 streams 0x2010
     PVT segments, TPDO1 reports 0x2012 buffer status + statusword,
     TPDO2 reports position/velocity).
  3. Tracks the CiA 402 state machine and Copley's PVT integrity counter.

PDO layout assumed (configure with apply_copley_pdo_remap_one.sh):
  RPDO1  ->  0x2010 (IP move segment, 64-bit, single PDO frame)
  RPDO2  ->  0x6040 ctrlword (16) + 0x6060 mode (8)
  TPDO1  ->  0x2012 buffer status (32) + 0x6041 statusword (16) + 0x6061 mode (8)
  TPDO2  ->  0x6064 position actual (32) + 0x606C velocity actual (32, counts/sec)
"""

from __future__ import annotations

import math
import threading
import time
from dataclasses import dataclass
from enum import Enum, auto
from typing import List, Optional, Tuple

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup, ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node

from sensor_msgs.msg import JointState
from std_msgs.msg import Bool, Float64MultiArray
from control_msgs.action import FollowJointTrajectory

from canopen_interfaces.srv import CORead, COWrite
from std_srvs.srv import Trigger
from epos2_bridge_interfaces.srv import MoveAbsoluteTimed

from copley_bridge import cia402
from copley_bridge.copley_ipm import (
    IDX_IP_MOVE_SEGMENT,
    IDX_TRAJ_BUFFER_STATUS,
    IntegrityCounter,
    PVTPoint,
    decode_buffer_status,
    pack_buffer_command_clear_abort,
    pack_buffer_command_clear_errors,
    pack_buffer_command_reset_segment_id,
    pack_end_of_move,
    pack_pvt_segment,
    sign_extend_24,
    to_signed_32,
)
from copley_bridge.raw_socket_can import RawSocketCAN


# Interpolation submode select (0x60C0, INTEGER8) for Copley alternative-
# objects PVT path (0x2010 buffer at COB 0x216). The drive honors this on
# every fresh IPM entry: 0 = linear PT (drive ignores velocity field and
# does not honor segment time as cubic-interpolation duration -- segments
# are consumed instantly and demand parks at the lead-in position), -1 =
# Copley PVT cubic. Empirically -1 is required on this firmware; without
# it the drive accepts segments, sets IPM Active, but never interpolates.
# Pass as 0xFF (two's-complement of -1 in i8) because the COWrite service
# data field is treated as unsigned.
COPLEY_IPM_SUBMODE_FOR_ALT_OBJECTS = 0xFF


class BridgeState(Enum):
    IDLE = auto()
    FAULTED = auto()
    READY = auto()
    IPM_ARMED = auto()
    MOVING = auto()


@dataclass
class JointKinematics:
    """Conversion between motor encoder counts and joint-space radians.

    Copley reports velocity in counts/sec (0x606C) -- different from
    EPOS2 which reports RPM. Encoder counts at 0x6064 are the same.
    """
    joint_name: str = "joint_0"
    encoder_qc_per_motor_rev: float = 0.0
    gear_ratio_motor_per_joint_rev: float = 0.0
    sign: float = 1.0
    zero_offset_qc: float = 0.0

    def is_configured(self) -> bool:
        return self.encoder_qc_per_motor_rev > 0.0 and self.gear_ratio_motor_per_joint_rev > 0.0

    def motor_qc_to_joint_rad(self, motor_qc: int) -> float:
        return (
            self.sign
            * (float(motor_qc) - self.zero_offset_qc)
            * 2.0 * math.pi
            / (self.encoder_qc_per_motor_rev * self.gear_ratio_motor_per_joint_rev)
        )

    def joint_rad_to_motor_qc(self, joint_rad: float) -> int:
        motor_qc = (
            self.zero_offset_qc
            + self.sign * joint_rad
            * (self.encoder_qc_per_motor_rev * self.gear_ratio_motor_per_joint_rev)
            / (2.0 * math.pi)
        )
        return int(round(motor_qc))

    def motor_ct_s_to_joint_rad_s(self, motor_ct_s: int) -> float:
        motor_rev_s = float(motor_ct_s) / self.encoder_qc_per_motor_rev
        joint_rev_s = motor_rev_s / self.gear_ratio_motor_per_joint_rev
        return self.sign * joint_rev_s * 2.0 * math.pi

    def joint_rad_s_to_motor_ct_s10(self, joint_rad_s: float) -> int:
        """Convert joint rad/s to motor counts/sec, then scale to 0.1 ct/s units."""
        motor_rev_s = self.sign * joint_rad_s / (2.0 * math.pi) * self.gear_ratio_motor_per_joint_rev
        motor_ct_s = motor_rev_s * self.encoder_qc_per_motor_rev
        return int(round(motor_ct_s * 10.0))


@dataclass
class DriveState:
    statusword: int = 0
    mode_display: int = 0
    buffer_status: int = 0          # raw 0x2012 value
    position_actual_qc: int = 0
    velocity_actual_ct_s: int = 0
    heartbeat_state: int = 0
    bus_operational: bool = False
    last_emcy_code: int = 0
    last_emcy_reg: int = 0
    last_update_ns: int = 0


class CopleyJointBridge(Node):

    # ------------------------------ init ------------------------------

    def __init__(self) -> None:
        super().__init__("copley_joint_bridge")

        self._declare_parameters()
        self._read_kinematics()
        if not self.kin.is_configured():
            self.get_logger().fatal(
                f"Encoder counts and gear ratio must be set for joint '{self.kin.joint_name}'. "
                "Override 'encoder_qc_per_motor_rev' and 'gear_ratio_motor_per_joint_rev' "
                "in the launch file or YAML config. Refusing to start."
            )
            raise RuntimeError("copley_bridge: kinematics not configured")

        self.drive_node_id = int(self.get_parameter("drive_node_id").value)
        self.can_interface = str(self.get_parameter("can_interface").value)

        # COB-IDs follow CiA 301 default layout
        self.cob_heartbeat = 0x700 + self.drive_node_id
        self.cob_rpdo1 = 0x200 + self.drive_node_id
        self.cob_rpdo2 = 0x300 + self.drive_node_id
        self.cob_tpdo1 = 0x180 + self.drive_node_id
        self.cob_tpdo2 = 0x280 + self.drive_node_id
        self.cob_emcy = 0x080 + self.drive_node_id

        self.state = DriveState()
        self.state_lock = threading.Lock()
        self.stream_lock = threading.Lock()

        self.bridge_state = BridgeState.IDLE
        self.ipm_armed = False
        self.last_hold_qc = 0
        self.integrity = IntegrityCounter()
        self.startup_complete = False

        # SDO clients (provided by an upstream canopen manager node).
        # Use a dedicated ReentrantCallbackGroup so the response callback
        # can be serviced on a different executor thread while a service
        # handler is polling the future. Otherwise the default exclusive
        # group makes call_async + poll deadlock against the handler.
        sdo_ns = f"/node_{self.drive_node_id}"
        self._sdo_cbg = ReentrantCallbackGroup()
        self.read_cli = self.create_client(
            CORead, f"{sdo_ns}/sdo_read", callback_group=self._sdo_cbg
        )
        self.write_cli = self.create_client(
            COWrite, f"{sdo_ns}/sdo_write", callback_group=self._sdo_cbg
        )

        # CAN socket for runtime PDO traffic
        self.can = RawSocketCAN(self.can_interface)

        # ROS interface
        self._setup_pubs_subs()
        self._setup_services()
        self._setup_action_server()

        # Background work
        self.rx_thread_running = True
        self.rx_thread = threading.Thread(target=self._can_rx_loop, daemon=True)
        self.rx_thread.start()

        self.create_timer(
            1.0 / float(self.get_parameter("joint_state_rate_hz").value),
            self._publish_joint_state,
        )

        self.create_timer(0.05, self._ipm_keepalive_cb)

        # Defer startup until SDO services are ready
        self.startup_timer = self.create_timer(0.5, self._startup_once)

        self.get_logger().info(
            f"copley_bridge for {self.kin.joint_name} on {self.can_interface} "
            f"node_id={self.drive_node_id}"
        )

    def _declare_parameters(self) -> None:
        self.declare_parameter("can_interface", "can0")
        self.declare_parameter("drive_node_id", 1)
        self.declare_parameter("joint_name", "joint0")
        self.declare_parameter("encoder_qc_per_motor_rev", 0.0)        # MUST override
        self.declare_parameter("gear_ratio_motor_per_joint_rev", 0.0)  # MUST override
        self.declare_parameter("sign", 1.0)
        self.declare_parameter("zero_offset_qc", 0.0)
        self.declare_parameter("joint_state_rate_hz", 50.0)
        self.declare_parameter("ipm_default_segment_ms", 100)
        self.declare_parameter("goal_position_tolerance_rad", 0.03)
        self.declare_parameter("fault_clear_on_startup", True)
        self.declare_parameter("enable_on_startup", False)
        self.declare_parameter("force_ipm_on_startup", False)
        self.declare_parameter("prearm_on_every_goal", True)

    def _read_kinematics(self) -> None:
        self.kin = JointKinematics(
            joint_name=str(self.get_parameter("joint_name").value),
            encoder_qc_per_motor_rev=float(self.get_parameter("encoder_qc_per_motor_rev").value),
            gear_ratio_motor_per_joint_rev=float(self.get_parameter("gear_ratio_motor_per_joint_rev").value),
            sign=float(self.get_parameter("sign").value),
            zero_offset_qc=float(self.get_parameter("zero_offset_qc").value),
        )

    def _setup_pubs_subs(self) -> None:
        self.pub_joint_states = self.create_publisher(JointState, "/joint_states", 10)
        self.pub_fault = self.create_publisher(Bool, "fault", 1)
        self.create_subscription(
            Float64MultiArray, "reduced_traj", self._reduced_traj_cb, 10
        )

    def _setup_services(self) -> None:
        cb = MutuallyExclusiveCallbackGroup()
        self.create_service(Trigger, "clear_fault", self._srv_clear_fault, callback_group=cb)
        self.create_service(Trigger, "arm_ipm", self._srv_arm_ipm, callback_group=cb)
        self.create_service(Trigger, "disarm_ipm", self._srv_disarm_ipm, callback_group=cb)
        self.create_service(
            MoveAbsoluteTimed, "move_absolute_timed",
            self._srv_move_absolute_timed, callback_group=cb,
        )

    def _setup_action_server(self) -> None:
        self.action_server = ActionServer(
            self,
            FollowJointTrajectory,
            f"/{self.kin.joint_name}_position_controller/follow_joint_trajectory",
            execute_callback=self._action_execute,
            goal_callback=self._action_goal,
            cancel_callback=self._action_cancel,
            callback_group=ReentrantCallbackGroup(),
        )

    # ------------------------------ SDO helpers ------------------------------

    def sdo_read(self, index: int, subindex: int, *, warn: bool = True) -> Optional[int]:
        if not self.read_cli.service_is_ready():
            if warn:
                self.get_logger().warning(f"SDO read not ready for 0x{index:04X}:{subindex}")
            return None
        req = CORead.Request()
        req.index = index
        req.subindex = subindex
        future = self.read_cli.call_async(req)
        # NOT spin_until_future_complete -- that nests executor spinning and
        # deadlocks when called from inside a service callback. Poll the
        # future status instead and let the MultiThreadedExecutor's other
        # threads service the SDO response.
        deadline = time.monotonic() + 0.5
        while not future.done() and time.monotonic() < deadline:
            time.sleep(0.005)
        if not future.done() or future.result() is None:
            if warn:
                self.get_logger().warning(f"SDO read 0x{index:04X}:{subindex} timed out")
            return None
        resp = future.result()
        if not getattr(resp, "success", True):
            if warn:
                self.get_logger().warning(f"SDO read 0x{index:04X}:{subindex} returned !success")
            return None
        return int(resp.data)

    def sdo_write(self, index: int, subindex: int, value: int, *, warn: bool = True) -> bool:
        if not self.write_cli.service_is_ready():
            if warn:
                self.get_logger().warning(f"SDO write not ready for 0x{index:04X}:{subindex}")
            return False
        req = COWrite.Request()
        req.index = index
        req.subindex = subindex
        req.data = int(value)
        future = self.write_cli.call_async(req)
        # Poll instead of nested spin -- see sdo_read comment for rationale.
        deadline = time.monotonic() + 0.5
        while not future.done() and time.monotonic() < deadline:
            time.sleep(0.005)
        if not future.done() or future.result() is None:
            if warn:
                self.get_logger().warning(f"SDO write 0x{index:04X}:{subindex} timed out")
            return False
        resp = future.result()
        return bool(getattr(resp, "success", True))

    # ------------------------------ State machine ------------------------------

    def _set_bridge_state(self, new_state: BridgeState, reason: str = "") -> None:
        if self.bridge_state != new_state:
            self.get_logger().info(
                f"Bridge state {self.bridge_state.name} -> {new_state.name}"
                + (f" ({reason})" if reason else "")
            )
        self.bridge_state = new_state

    def _wait_for_sw_match(self, mask: int, expected: int, timeout: float = 1.0):
        """Poll statusword until (sw & mask) == expected. Return last sw or None."""
        deadline = time.monotonic() + timeout
        last_sw = None
        while time.monotonic() < deadline:
            sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
            if sw is not None:
                last_sw = sw & 0xFFFF
                if (last_sw & mask) == expected:
                    return last_sw
            time.sleep(0.02)
        return last_sw

    def clear_fault(self) -> bool:
        sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
        if sw is not None and not cia402.sw_faulted(sw & 0xFFFF):
            self.get_logger().info(
                f"clear_fault: drive not faulted, sw=0x{sw & 0xFFFF:04X}"
            )
            self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_SHUTDOWN, warn=False)
            # Recover bridge state if it was stuck in FAULTED but drive is OK.
            if self.bridge_state == BridgeState.FAULTED:
                self.ipm_armed = False
                self._set_bridge_state(
                    BridgeState.READY,
                    "clear_fault: drive healthy, recovering bridge from FAULTED",
                )
            return True
        # Copley-specific: clear any latched faults in 0x2183 first.
        # Write 0xFFFFFFFF clears all clearable bits; reads-on-read style
        # registers (0x2180) aren't touched here.
        latched = self.sdo_read(0x2183, 0, warn=False)
        if latched is not None and (latched & 0xFFFFFFFF) != 0:
            self.get_logger().info(
                f"clear_fault: clearing 0x2183=0x{latched & 0xFFFFFFFF:08X}"
            )
            self.sdo_write(0x2183, 0, 0xFFFFFFFF, warn=False)
            time.sleep(0.02)
        # Rising-edge fault reset on ctrlword bit 7.
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, 0x00, warn=False)
        time.sleep(0.01)
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_FAULT_RESET)
        time.sleep(0.05)
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, 0x00, warn=False)
        cleared_sw = self._wait_for_sw_match(
            1 << cia402.SW_BIT_FAULT, 0, timeout=1.0
        )
        if cleared_sw is None:
            self.get_logger().error("clear_fault: no statusword response")
            return False
        if cia402.sw_faulted(cleared_sw):
            self.get_logger().error(
                f"clear_fault: fault bit still set after reset, sw=0x{cleared_sw:04X}"
            )
            return False
        # Now issue Shutdown -> Ready-to-switch-on instead of Switch-on-disabled.
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_SHUTDOWN, warn=False)
        final_sw = self._wait_for_sw_match(0x6F, 0x21, timeout=0.5)
        self.get_logger().info(
            f"clear_fault: cleared, sw=0x{(final_sw if final_sw is not None else cleared_sw):04X}"
        )
        return True

    def set_mode(self, mode: int) -> bool:
        return self.sdo_write(cia402.IDX_MODES_OF_OPERATION, 0, mode)

    def enable_operation(self) -> bool:
        # Verify starting point: not in fault.
        sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
        if sw is None:
            self.get_logger().error("enable_operation: no statusword")
            return False
        sw &= 0xFFFF
        if cia402.sw_faulted(sw):
            self.get_logger().warn(
                f"enable_operation: drive faulted (sw=0x{sw:04X}), attempting clear"
            )
            if not self.clear_fault():
                return False
        # Step 1: Shutdown -> Ready to Switch On (bits: 0=1, 1=0, 2=0, 3=0, 6=0)
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_SHUTDOWN)
        sw = self._wait_for_sw_match(0x6F, 0x21, timeout=1.0)
        if sw is None or (sw & 0x6F) != 0x21:
            self.get_logger().error(
                f"enable_operation: failed Shutdown->Ready, sw=0x{(sw or 0):04X}"
            )
            return False
        # Step 2: Switch On -> Switched On (bits: 0=1, 1=1, 2=0, 3=0, 6=0)
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_SWITCH_ON)
        sw = self._wait_for_sw_match(0x6F, 0x23, timeout=1.0)
        if sw is None or (sw & 0x6F) != 0x23:
            self.get_logger().error(
                f"enable_operation: failed Switch On->Switched On, sw=0x{(sw or 0):04X}"
            )
            return False
        # Step 3: Enable Operation (bits: 0=1, 1=1, 2=1, 3=0, 6=0)
        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_ENABLE_OPERATION)
        sw = self._wait_for_sw_match(0x6F, 0x27, timeout=1.0)
        if sw is None:
            self.get_logger().error("enable_operation: no sw after CW=0x0F")
            return False
        self.get_logger().info(f"enable_operation final sw=0x{sw:04X}")
        if cia402.sw_faulted(sw):
            self.get_logger().error(
                f"enable_operation: drive faulted during enable, sw=0x{sw:04X}"
            )
            return False
        return cia402.sw_operation_enabled(sw)

    def clear_buffer(self) -> bool:
        """Send a 'clear buffer + abort' command frame on RPDO1.

        On Copley, buffer clear is done via the 0x2010 streaming object
        with the buffer-command bit set, NOT via an SDO write. Doing it
        on RPDO1 keeps it on the same path as the streaming traffic.
        """
        try:
            # NOTE: this Copley firmware needs ~50ms between buffer commands
            # for them to actually settle. With 5ms gaps subsequent data
            # segments are silently rejected. Manual diagnostic confirmed
            # 50ms works.
            self.can.send(self.cob_rpdo1, pack_buffer_command_clear_abort())
            time.sleep(0.05)
            # mask 0x07 = seq_err + overflow + underflow. Without this, the
            # latched seq_err bit (set by previous end-of-move or earlier
            # session) makes the drive reject every new PVT segment.
            self.can.send(self.cob_rpdo1, pack_buffer_command_clear_errors(0x07))
            time.sleep(0.05)
            self.can.send(self.cob_rpdo1, pack_buffer_command_reset_segment_id())
            self.integrity.reset()
            time.sleep(0.10)  # let the drive's state reset settle
            return True
        except Exception as exc:
            self.get_logger().error(f"clear_buffer failed: {exc}")
            return False

    def _verify_pdo_mapping(self) -> bool:
        """Read back the four critical PDO mappings and warn if they don't match.

        We don't reconfigure -- if the mappings are wrong, the operator
        needs to run apply_copley_pdo_remap_one.sh before starting the
        bridge. We just refuse to arm if the streaming wouldn't work.
        """
        expected = {
            (0x1600, 1, "RPDO1[1]"): 0x20100040,
            (0x1A00, 1, "TPDO1[1]"): 0x20120020,
            (0x1A01, 1, "TPDO2[1]"): 0x60640020,
            (0x1A01, 2, "TPDO2[2]"): 0x606C0020,
        }
        all_ok = True
        for (idx, sub, label), want in expected.items():
            got = self.sdo_read(idx, sub, warn=False)
            if got is None:
                self.get_logger().warning(f"PDO mapping {label} could not be read")
                all_ok = False
                continue
            got &= 0xFFFFFFFF
            if got != want:
                self.get_logger().error(
                    f"PDO mapping {label} = 0x{got:08X}, expected 0x{want:08X}. "
                    "Run scripts/apply_copley_pdo_remap_one.sh before bringup."
                )
                all_ok = False
        return all_ok

    def startup_ipm(self) -> bool:
        self.get_logger().info("Arming IPM (Copley alternative-objects path)")
        self.ipm_armed = False
        self._set_bridge_state(BridgeState.IDLE, "starting arm sequence")

        try:
            if not self._verify_pdo_mapping():
                self._set_bridge_state(BridgeState.FAULTED, "PDO mapping verification failed")
                return False

            sw0 = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
            if sw0 is not None and cia402.sw_faulted(sw0):
                if not self.clear_fault():
                    self._set_bridge_state(BridgeState.FAULTED, "clear_fault failed")
                    return False
                time.sleep(0.05)

            if not self.set_mode(cia402.MODE_INTERPOLATED_POSITION):
                self._set_bridge_state(BridgeState.FAULTED, "failed to set IPM mode")
                return False

            # Must be -1 (Copley PVT cubic). With 0 the drive treats every
            # PVT segment as linear PT, drains the buffer in ~250 ms regardless
            # of segment time, and parks demand at the lead-in position.
            self.sdo_write(cia402.IDX_INTERPOLATION_SUBMODE, 0,
                           COPLEY_IPM_SUBMODE_FOR_ALT_OBJECTS, warn=False)

            if not self.enable_operation():
                self._set_bridge_state(BridgeState.FAULTED, "enable_operation failed")
                return False

            if not self.clear_buffer():
                self._set_bridge_state(BridgeState.FAULTED, "buffer clear failed")
                return False

            current_pos = self.sdo_read(cia402.IDX_POSITION_ACTUAL, 0, warn=False)
            if current_pos is None:
                self._set_bridge_state(BridgeState.FAULTED, "no current position")
                return False
            current_qc = to_signed_32(current_pos)
            self.last_hold_qc = current_qc

            if abs(current_qc) >= (1 << 23):
                self.get_logger().warning(
                    f"Current position {current_qc} exceeds 24-bit PVT range; "
                    "consider using a 32-bit preload segment (not yet implemented)."
                )

            # Transactional pattern: NO prefill, NO ctrlword 0x1F here.
            # execute_pvt_trajectory does its own clear+prefill+0x1F+wait+0x0F.
            # Drive sits in Op Enabled, mode=7, ctrlword=0x0F until a move arrives.

            sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
            buf = self.sdo_read(IDX_TRAJ_BUFFER_STATUS, 0, warn=False)

            if sw is not None:
                self.state.statusword = sw & 0xFFFF
            if buf is not None:
                self.state.buffer_status = buf & 0xFFFFFFFF

            sw_hex = f"0x{sw:04X}" if sw is not None else "None"
            buf_hex = f"0x{buf:08X}" if buf is not None else "None"
            self.get_logger().info(f"startup_ipm final sw={sw_hex} buffer_status={buf_hex}")

            if sw is not None and cia402.sw_faulted(sw):
                self._set_bridge_state(BridgeState.FAULTED, "fault during arm")
                return False

            if buf is None:
                self._set_bridge_state(BridgeState.FAULTED, "no buffer status after arm")
                return False

            decoded = decode_buffer_status(buf)
            if decoded.has_error:
                # Non-fatal: each trajectory starts with its own clear_buffer
                # that will wipe these latched bits.
                self.get_logger().warning(
                    f"Buffer error bits set after arm (seq_err={decoded.sequence_error} "
                    f"overflow={decoded.overflow} underflow={decoded.underflow}); "
                    "will be cleared at next trajectory start"
                )

            self.ipm_armed = True
            self._set_bridge_state(BridgeState.IPM_ARMED, "IPM active and buffered")
            self.get_logger().info(
                f"IPM armed successfully, free_count={decoded.free_count} "
                f"next_seg_id={decoded.next_segment_id}"
            )
            return True

        except Exception as exc:
            self.get_logger().error(f"startup_ipm exception: {exc}")
            self._set_bridge_state(BridgeState.FAULTED, "startup_ipm exception")
            self.ipm_armed = False
            return False

    def disarm_ipm(self) -> bool:
        self.ipm_armed = False
        # End-of-move sentinel lets the drive settle on the present setpoint
        try:
            self.can.send(self.cob_rpdo1, pack_end_of_move(self.integrity.next(), position_qc=self.last_hold_qc))
        except Exception:
            pass
        time.sleep(0.05)
        ok = self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_ENABLE_OPERATION)
        self._set_bridge_state(BridgeState.READY, "disarm")
        return ok

    # ------------------------------ Streaming ------------------------------

    def _send_pvt_segment(self, point: PVTPoint) -> None:
        payload = pack_pvt_segment(point, self.integrity.next())
        self.can.send(self.cob_rpdo1, payload)

    def _read_buffer_state(self):
        """Read 0x2012 and decode it. Returns dict or None on read failure."""
        buf = self.sdo_read(0x2012, 0, warn=False)
        if buf is None:
            return None
        free = (buf >> 16) & 0xFF
        return {
            "raw": buf & 0xFFFFFFFF,
            "free": free,
            "occupancy": 64 - free,
            "next_seg_id": buf & 0xFFFF,
            "err_seq": bool((buf >> 24) & 0x01),
            "err_overflow": bool((buf >> 25) & 0x01),
            "err_underflow": bool((buf >> 26) & 0x01),
            "any_error": bool((buf >> 24) & 0x07),
            "empty": bool((buf >> 31) & 0x01),
        }

    def _stream_pvt_with_flow_control(self, segments, final_qc):
        """Producer-consumer streaming of PVT segments to the drive.

        State machine:
          1. Top up: poll 0x2012, push segments while occupancy < HIGH_WATER.
          2. Start: once INITIAL_FILL queued (or all for short moves), write
             controlword 0x1F to rising-edge IPM; drive begins consuming.
          3. Continue topping up as drive drains.
          4. EOM: time=0 segment carrying final_qc, after last data segment.

        Returns False on buffer error or timeout.
        """
        BUFFER_DEPTH = 64
        # INITIAL_FILL: pre-roll depth before starting IPM. Bumped from 24 so
        # the drive has a deep working set on long trajectories where bridge
        # may briefly fall behind drive consumption.
        INITIAL_FILL = 40
        # HIGH_WATER: max occupancy we let the buffer reach. Kept close to
        # BUFFER_DEPTH (4-slot safety margin) so the drive never drains while
        # bridge is still streaming. Underflow risk dominates overflow risk.
        HIGH_WATER = 60
        # MIN_BURST = 1: refill on any free slot. With MIN_BURST > 1 the
        # bridge waited POLL_INTERVAL_S whenever free < MIN_BURST, which
        # capped throughput at roughly the drive consumption rate -- zero
        # margin for jitter. Always sending available room avoids underflow.
        MIN_BURST = 1
        POLL_INTERVAL_S = 0.01
        STREAM_TIMEOUT_S = max(30.0, len(segments) * 0.5)

        total = len(segments)
        sent = 0
        ipm_started = False
        deadline = time.monotonic() + STREAM_TIMEOUT_S

        self.get_logger().info(
            f"_stream_pvt: total={total} initial_fill={INITIAL_FILL} "
            f"high_water={HIGH_WATER}"
        )

        while sent < total:
            if time.monotonic() > deadline:
                self.get_logger().error(
                    f"_stream_pvt: timeout after sending {sent}/{total} segments"
                )
                return False

            state = self._read_buffer_state()
            if state is None:
                time.sleep(0.005)
                continue

            if state["any_error"]:
                self.get_logger().error(
                    f"_stream_pvt: buffer error 0x{state['raw']:08X} "
                    f"(seq_err={state['err_seq']} overflow={state['err_overflow']} "
                    f"underflow={state['err_underflow']}) after {sent}/{total} segments"
                )
                return False

            room = HIGH_WATER - state["occupancy"]
            burst = min(room, total - sent)

            if burst < MIN_BURST and sent < total:
                time.sleep(POLL_INTERVAL_S)
                continue

            for _ in range(burst):
                self._send_pvt_segment(segments[sent])
                sent += 1
                # Gentle pacing: keep CAN tx queue from being slammed and let
                # other RPDO1 senders (J0/J2 on shared bus) get arbitration
                # slots. Without this, simultaneous multi-joint MoveIt plans
                # can starve our PVT frames on bus arbitration, causing the
                # drive to see an integrity gap and latch seq_err.
                time.sleep(0.001)

            if not ipm_started and (sent >= INITIAL_FILL or sent >= total):
                # Let the just-queued segments commit in the drive's buffer
                # before rising-edging bit 4 to transition to IPM Active.
                time.sleep(0.02)
                self.sdo_write(
                    cia402.IDX_CONTROLWORD, 0, cia402.CW_START_IPM_MOVE, warn=False
                )
                time.sleep(0.005)
                ipm_started = True
                self.get_logger().info(
                    f"_stream_pvt: IPM started after queuing {sent}/{total} segments"
                )

        self.can.send(
            self.cob_rpdo1,
            pack_end_of_move(self.integrity.next(), position_qc=final_qc),
        )

        if not ipm_started:
            self.sdo_write(
                cia402.IDX_CONTROLWORD, 0, cia402.CW_START_IPM_MOVE, warn=False
            )
            time.sleep(0.005)
            self.get_logger().info(
                f"_stream_pvt: IPM started after queuing all {total} segments"
            )

        return True

    def _ipm_keepalive_cb(self) -> None:
        # Disabled in transactional pattern. With keepalive enabled, the bridge
        # streamed hold PVT packets at 20Hz between trajectories, which caused
        # the drive's segment-ID counter to drift out of sync over tens of
        # seconds of idle, leading to seq_err on the first move after a long
        # idle period. The drive's position loop holds at the last commanded
        # position via Operation Enabled state -- it does not need periodic
        # PVT packets.
        return
        if not self.ipm_armed:
            return
        if self.bridge_state != BridgeState.IPM_ARMED:
            return

        seg_ms = max(20, int(self.get_parameter("ipm_default_segment_ms").value))
        hold = PVTPoint(time_ms=seg_ms, velocity_ct_s10=0, position_qc=self.last_hold_qc)
        try:
            self._send_pvt_segment(hold)
        except Exception as exc:
            self.get_logger().error(f"IPM keepalive send failed: {exc}")

    def execute_pvt_trajectory(
        self,
        target_rads: List[float],
        target_vel_rad_s: List[float],
        duration_secs: List[float],
    ) -> bool:
        if not self.ipm_armed:
            self.get_logger().warning("IPM not armed; call arm_ipm first")
            return False
        n_in = len(target_rads)
        if n_in == 0 or len(target_vel_rad_s) != n_in or len(duration_secs) != n_in:
            self.get_logger().error("execute_pvt_trajectory got mismatched or empty arrays")
            return False

        with self.stream_lock:
            if self.bridge_state not in (BridgeState.IPM_ARMED, BridgeState.MOVING):
                self.get_logger().warning(
                    f"Refusing PVT trajectory in state {self.bridge_state.name}"
                )
                return False

            current_pos = self.sdo_read(cia402.IDX_POSITION_ACTUAL, 0, warn=False)
            if current_pos is None:
                self.get_logger().error("Failed reading current position for PVT trajectory")
                return False
            current_qc = to_signed_32(current_pos)
            current_rad = self.kin.motor_qc_to_joint_rad(current_qc)

            points: List[PVTPoint] = []
            prev_q = current_rad
            prev_v = 0.0
            for q, v, dt in zip(target_rads, target_vel_rad_s, duration_secs):
                q = float(q)
                v = float(v)
                dt = max(0.03, float(dt))
                # Time field is u8 in ms, max 255 ms per segment; subdivide if needed.
                n = max(1, math.ceil(dt / 0.255))
                for k in range(1, n + 1):
                    frac = k / n
                    qk = prev_q + frac * (q - prev_q)
                    vk = prev_v + frac * (v - prev_v)
                    dtk = dt / n

                    pos_qc = self.kin.joint_rad_to_motor_qc(qk)
                    vel_ct_s10 = self.kin.joint_rad_s_to_motor_ct_s10(vk)

                    points.append(PVTPoint(
                        time_ms=max(20, min(255, int(round(dtk * 1000.0)))),
                        velocity_ct_s10=int(vel_ct_s10),
                        position_qc=int(pos_qc),
                    ))
                prev_q = q
                prev_v = v

            if not points:
                self.get_logger().warning("PVT trajectory produced no executable points")
                return False

            # 24-bit position-range guard (we only emit format-code-0 segments).
            for pt in points:
                if abs(pt.position_qc) >= (1 << 23):
                    self.get_logger().error(
                        f"Trajectory point position {pt.position_qc} exceeds 24-bit PVT range. "
                        "Rebase the joint zero offset or use a 32-bit preload segment."
                    )
                    return False

            self.get_logger().info(
                f"PVT packetization: {n_in} knots -> {len(points)} segments"
            )            # Goal-arrival preflight:
            # A 48 V bus interruption can leave the bridge's cached state stale.
            # Mirror the known-good service recovery path before every PVT stream.
            try:
                do_prearm = bool(self.get_parameter("prearm_on_every_goal").value)
            except Exception:
                do_prearm = True
            
            if do_prearm:
                self.get_logger().info(
                    "Copley FJT preflight v4: clear_fault + startup_ipm before PVT stream"
                )
                try:
                    ok_clear = self.clear_fault()
                    ok_start = self.startup_ipm()
                except Exception as exc:
                    self.get_logger().error("Copley FJT preflight exception: " + str(exc))
                    _preflight_result = FollowJointTrajectory.Result()
                    _preflight_result.error_code = FollowJointTrajectory.Result.PATH_TOLERANCE_VIOLATED
                    _preflight_result.error_string = "Copley FJT preflight exception: " + str(exc)
                    try:
                        goal_handle.abort()
                    except Exception:
                        pass
                    return _preflight_result
            
                if not (ok_clear and ok_start):
                    self.get_logger().error(
                        "Copley FJT preflight failed: "
                        + "clear=" + str(ok_clear)
                        + " startup=" + str(ok_start)
                    )
                    _preflight_result = FollowJointTrajectory.Result()
                    _preflight_result.error_code = FollowJointTrajectory.Result.PATH_TOLERANCE_VIOLATED
                    _preflight_result.error_string = "Copley FJT preflight failed"
                    try:
                        goal_handle.abort()
                    except Exception:
                        pass
                    return _preflight_result
            


            self._set_bridge_state(BridgeState.MOVING, "executing PVT trajectory")

            try:
                # Transactional IPM pattern: every trajectory is its own IPM
                # session. Force ctrlword bit 4 low so the 0x1F write later
                # makes a real 0->1 transition and the drive actually starts
                # interpolating.
                self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_ENABLE_OPERATION, warn=False)
                time.sleep(0.01)
                # Clear buffer + error bits + reset segment ID. Drive's
                # expected-next-segment-id resets to 0, error flags clear,
                # any stale segments are dropped. The bridge's integrity
                # counter resets to 0 inside clear_buffer().
                if not self.clear_buffer():
                    self.get_logger().error("clear_buffer failed at trajectory start")
                    self._set_bridge_state(BridgeState.FAULTED, "clear_buffer failed at trajectory start")
                    return False

                # Build the full segment queue: lead-in + trajectory + hold tail.
                # The hold tail gives a soft landing if EOM is delayed; the
                # lead-in gives the drive ~40 ms of slack to spin up.
                final_qc = points[-1].position_qc
                self.last_hold_qc = final_qc

                all_segments = []
                all_segments.append(
                    PVTPoint(time_ms=40, velocity_ct_s10=0, position_qc=current_qc)
                )
                all_segments.extend(points)
                for _ in range(8):
                    all_segments.append(
                        PVTPoint(time_ms=40, velocity_ct_s10=0, position_qc=final_qc)
                    )

                # Producer-consumer state machine: tops up the drive buffer as
                # it drains, writes ctrlword 0x1F at the right moment, and
                # sends EOM after the last data segment.
                if not self._stream_pvt_with_flow_control(all_segments, final_qc):
                    # Drop ctrlword bit 4 so the drive exits IPM Active
                    # gracefully at its current demand instead of snapping
                    # to a stale register value (causing a violent PID-back).
                    self._safe_exit_ipm()
                    self.ipm_armed = False
                    self._set_bridge_state(BridgeState.FAULTED, "PVT streaming failed")
                    return False

                tolerance = float(self.get_parameter("goal_position_tolerance_rad").value)
                total_wait = sum(max(0.03, float(d)) for d in duration_secs) + 2.5
                deadline = time.monotonic() + max(total_wait, 2.0)
                final_target_rad = float(target_rads[-1])

                # Wait for the drive to actually finish. We require:
                #   (a) the drive was observed in IPM Active at some point
                #       since this loop began (so we don't early-exit when
                #       the drive never entered IPM at all -- a sign of a
                #       broken arm/prefill)
                #   (b) AND the drive has now exited IPM Active OR buffer
                #       is empty (drive consumed all segments incl. EOM)
                #   (c) AND |actual - target| <= tolerance
                # Early-exit with False on fault or any buffer error bit.
                saw_ipm_active = False
                while time.monotonic() < deadline:
                    sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
                    if sw is not None and cia402.sw_faulted(sw):
                        self.get_logger().error(f"Fault during PVT trajectory, sw=0x{sw:04X}")
                        self._safe_exit_ipm()
                        self.ipm_armed = False
                        self._set_bridge_state(BridgeState.FAULTED, "fault during PVT")
                        return False

                    buf = self.sdo_read(IDX_TRAJ_BUFFER_STATUS, 0, warn=False)
                    if buf is not None:
                        decoded = decode_buffer_status(buf)
                        if decoded.has_error:
                            self.get_logger().error(
                                f"Buffer error during PVT: 0x{buf & 0xFFFFFFFF:08X} "
                                f"(seq_err={decoded.sequence_error} "
                                f"overflow={decoded.overflow} "
                                f"underflow={decoded.underflow})"
                            )
                            self.ipm_armed = False
                            self._set_bridge_state(BridgeState.FAULTED, "buffer error during PVT")
                            return False

                    pos = self.sdo_read(cia402.IDX_POSITION_ACTUAL, 0, warn=False)
                    if pos is None:
                        time.sleep(0.02)
                        continue
                    pos_rad = self.kin.motor_qc_to_joint_rad(to_signed_32(pos))

                    ipm_active_now = (sw is not None) and cia402.sw_ipm_active(sw)
                    if ipm_active_now:
                        saw_ipm_active = True

                    ipm_exited = saw_ipm_active and not ipm_active_now
                    buf_empty = (buf is not None) and bool((buf >> 31) & 0x1)
                    drive_idle = ipm_exited or (saw_ipm_active and buf_empty)
                    at_target = abs(final_target_rad - pos_rad) <= tolerance

                    if drive_idle and at_target:
                        # Drop ctrlword bit 4 so the drive sits in Operation
                        # Enabled hold (no IPM active). Position loop holds at
                        # the final commanded position. Next trajectory will
                        # rising-edge bit 4 again to start a fresh IPM session.
                        self.sdo_write(cia402.IDX_CONTROLWORD, 0, cia402.CW_ENABLE_OPERATION, warn=False)
                        self.get_logger().info(
                            f"PVT trajectory complete: pos={pos_rad:.6f} target={final_target_rad:.6f} "
                            f"sw=0x{(sw or 0) & 0xFFFF:04X} buf=0x{(buf or 0) & 0xFFFFFFFF:08X}"
                        )
                        self._set_bridge_state(BridgeState.IPM_ARMED, "PVT trajectory complete")
                        return True
                    time.sleep(0.02)

                self.get_logger().error(
                    "PVT trajectory timed out before completion: "
                    f"pos={pos_rad if 'pos_rad' in dir() else 'N/A'} target={final_target_rad}"
                )
                self._set_bridge_state(BridgeState.IPM_ARMED, "PVT trajectory timeout")
                return False

            except Exception as exc:
                self.get_logger().error(f"PVT trajectory exception: {exc}")
                self._safe_exit_ipm()
                self.ipm_armed = False
                self._set_bridge_state(BridgeState.FAULTED, "PVT trajectory exception")
                return False

    def _safe_exit_ipm(self) -> None:
        """Drop ctrlword bit 4 to exit IPM Active without changing PID state.

        Call this when the bridge needs to abandon a streaming session
        (buffer error, timeout, exception) but wants the drive to hold
        position at the last commanded demand rather than snap to a stale
        register value. Drive stays in Operation Enabled (PWM on, PID
        active) holding at last 0x6062.
        """
        try:
            self.sdo_write(
                cia402.IDX_CONTROLWORD, 0, cia402.CW_ENABLE_OPERATION, warn=False
            )
            time.sleep(0.01)
        except Exception as exc:
            self.get_logger().warning(f"_safe_exit_ipm: {exc}")


    # ------------------------------ CAN RX ------------------------------

    def _can_rx_loop(self) -> None:
        while self.rx_thread_running:
            try:
                msg = self.can.recv()
            except OSError:
                if not self.rx_thread_running:
                    break
                continue
            if msg is None:
                continue
            can_id, data = msg
            now_ns = self.get_clock().now().nanoseconds

            with self.state_lock:
                self.state.last_update_ns = now_ns
                if can_id == self.cob_heartbeat and len(data) >= 1:
                    self.state.heartbeat_state = data[0]
                    self.state.bus_operational = (data[0] == 0x05)
                elif can_id == self.cob_tpdo1 and len(data) >= 7:
                    # 0x2012 (32) + 0x6041 (16) + 0x6061 (8) = 7 bytes, LSB-first
                    buf = (data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24))
                    sw = data[4] | (data[5] << 8)
                    mode = data[6]
                    self.state.buffer_status = buf & 0xFFFFFFFF
                    self.state.statusword = sw & 0xFFFF
                    self.state.mode_display = mode
                elif can_id == self.cob_tpdo2 and len(data) >= 8:
                    pos_u32 = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24)
                    vel_u32 = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24)
                    self.state.position_actual_qc = to_signed_32(pos_u32)
                    self.state.velocity_actual_ct_s = to_signed_32(vel_u32)
                elif can_id == self.cob_emcy and len(data) >= 3:
                    self.state.last_emcy_code = data[0] | (data[1] << 8)
                    self.state.last_emcy_reg = data[2]

    # ------------------------------ Publishers ------------------------------

    def _publish_joint_state(self) -> None:
        with self.state_lock:
            motor_qc = self.state.position_actual_qc
            motor_ct_s = self.state.velocity_actual_ct_s
            faulted = cia402.sw_faulted(self.state.statusword)

        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.name = [self.kin.joint_name]
        msg.position = [self.kin.motor_qc_to_joint_rad(motor_qc)]
        msg.velocity = [self.kin.motor_ct_s_to_joint_rad_s(motor_ct_s)]
        msg.effort = []
        self.pub_joint_states.publish(msg)

        fmsg = Bool()
        fmsg.data = bool(faulted)
        self.pub_fault.publish(fmsg)

    # ------------------------------ Startup ------------------------------

    def _startup_once(self) -> None:
        if self.startup_complete:
            return
        if not (self.read_cli.service_is_ready() and self.write_cli.service_is_ready()):
            return
        self.get_logger().info("Running one-time startup sequence")

        if bool(self.get_parameter("fault_clear_on_startup").value):
            self.clear_fault()

        # Optional: confirm the drive is in CANopen-controlled servo mode.
        # CMO-saved drives should already have 0x2300 = 30 (CANopen drives
        # the position loop). If it's anything else, motion commands will
        # be silently ignored.
        desired_state = self.sdo_read(0x2300, 0, warn=False)
        if desired_state is not None and (desired_state & 0xFFFF) != 30:
            self.get_logger().error(
                f"Desired State (0x2300) = {desired_state & 0xFFFF}, expected 30 "
                "(servo position loop driven by CANopen). Re-save in CME with "
                "CANopen-driven position control selected."
            )

        if bool(self.get_parameter("force_ipm_on_startup").value):
            self.set_mode(cia402.MODE_INTERPOLATED_POSITION)

        if bool(self.get_parameter("enable_on_startup").value):
            self.enable_operation()

        self.startup_complete = True
        self.startup_timer.cancel()
        self._set_bridge_state(BridgeState.READY, "startup complete")

    # ------------------------------ Service handlers ------------------------------

    def _srv_clear_fault(self, request, response):
        ok = self.clear_fault()
        response.success = bool(ok)
        response.message = "fault cleared" if ok else "fault clear failed"
        return response

    def _srv_arm_ipm(self, request, response):
        ok = self.startup_ipm()
        response.success = bool(ok)
        response.message = "IPM armed" if ok else "IPM arm failed"
        return response

    def _srv_disarm_ipm(self, request, response):
        ok = self.disarm_ipm()
        response.success = bool(ok)
        response.message = "IPM disarmed" if ok else "disarm failed"
        return response

    def _srv_move_absolute_timed(self, request, response):
        target = float(request.target_rad)
        duration = max(0.05, float(request.duration_sec))
        ok = self.execute_pvt_trajectory([target], [0.0], [duration])
        if ok:
            with self.state_lock:
                final_rad = self.kin.motor_qc_to_joint_rad(self.state.position_actual_qc)
            err = abs(target - final_rad)
            response.success = err <= float(self.get_parameter("goal_position_tolerance_rad").value)
            response.message = f"err={err:.4f} rad"
        else:
            response.success = False
            response.message = "execute_pvt_trajectory returned false"
        return response

    # ------------------------------ /reduced_traj ------------------------------

    def _reduced_traj_cb(self, msg: Float64MultiArray) -> None:
        data = list(msg.data)
        if len(data) % 3 != 0 or not data:
            self.get_logger().warning(
                "Ignoring /reduced_traj: expected [q,v,dt,...] flat array (3*N)"
            )
            return
        qs = data[0::3]
        vs = data[1::3]
        dts = data[2::3]
        self.execute_pvt_trajectory(qs, vs, dts)

    # ------------------------------ Action server ------------------------------

    def _action_goal(self, goal_request) -> GoalResponse:
        names = list(goal_request.trajectory.joint_names)
        if names != [self.kin.joint_name]:
            self.get_logger().warning(
                f"Rejecting trajectory for joint_names={names}, expected [{self.kin.joint_name}]"
            )
            return GoalResponse.REJECT
        if not goal_request.trajectory.points:
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _action_cancel(self, goal_handle) -> CancelResponse:
        return CancelResponse.ACCEPT

    def _ensure_ready_for_trajectory(self) -> Tuple[bool, str]:
        """Bring the bridge into IPM_ARMED before executing a trajectory.

        Tolerates arriving in FAULTED state: calls clear_fault once, checks
        the statusword to confirm the drive actually recovered (latched
        faults won't clear), then re-arms. Avoids requiring the operator to
        manually call clear_fault + arm_ipm before every plan.
        """
        if self.bridge_state == BridgeState.FAULTED:
            self.get_logger().warning(
                "Bridge FAULTED on trajectory arrival; attempting clear_fault"
            )
            self.clear_fault()
            sw = self.sdo_read(cia402.IDX_STATUSWORD, 0, warn=False)
            if sw is None:
                return False, "no statusword after clear_fault"
            if cia402.sw_faulted(sw & 0xFFFF):
                return False, (
                    f"drive still faulted after clear_fault "
                    f"(latched, sw=0x{sw & 0xFFFF:04X})"
                )
            # Drive is clean. Drop FAULTED so startup_ipm runs from a known state.
            self.ipm_armed = False
            self._set_bridge_state(BridgeState.READY, "clear_fault recovered drive")

        if not self.ipm_armed:
            if not self.startup_ipm():
                return False, "Failed to arm IPM"

        return True, ""

    def _action_execute(self, goal_handle):
        traj = goal_handle.request.trajectory

        ok, reason = self._ensure_ready_for_trajectory()
        if not ok:
            goal_handle.abort()
            result = FollowJointTrajectory.Result()
            result.error_code = FollowJointTrajectory.Result.PATH_TOLERANCE_VIOLATED
            result.error_string = reason
            return result

        qs: List[float] = []
        vs: List[float] = []
        dts: List[float] = []
        prev_t = 0.0
        for pt in traj.points:
            t = float(pt.time_from_start.sec) + float(pt.time_from_start.nanosec) * 1e-9
            dt = max(0.03, t - prev_t)
            prev_t = t
            qs.append(float(pt.positions[0]) if pt.positions else 0.0)
            vs.append(float(pt.velocities[0]) if pt.velocities else 0.0)
            dts.append(dt)

        ok = self.execute_pvt_trajectory(qs, vs, dts)
        result = FollowJointTrajectory.Result()
        if ok:
            goal_handle.succeed()
            result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
        else:
            goal_handle.abort()
            result.error_code = FollowJointTrajectory.Result.PATH_TOLERANCE_VIOLATED
            result.error_string = "Trajectory execution failed"
        return result

    # ------------------------------ Shutdown ------------------------------

    def destroy_node(self) -> bool:
        self.rx_thread_running = False
        try:
            if self.rx_thread.is_alive():
                self.rx_thread.join(timeout=1.0)
        except Exception:
            pass
        try:
            self.can.close()
        except Exception:
            pass
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = CopleyJointBridge()
    executor = MultiThreadedExecutor(num_threads=4)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
