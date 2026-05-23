#!/usr/bin/env python3
import json
import math
import numpy as np
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseArray, Pose
from scipy.spatial.transform import Rotation as R
from std_msgs.msg import String, Bool

# tf2 imports for coordinate frame transform
from tf2_ros import Buffer, TransformListener, LookupException, ExtrapolationException
import tf2_geometry_msgs
from geometry_msgs.msg import PointStamped

from robot_interfaces.srv import GetPoses

CONFIDENCE_THRESHOLD = 0.6   # ignore low-confidence detections
APPROACH_STANDOFF    = 0.05  # 5 cm before tomato surface on approach
RETRACT_STANDOFF     = 0.15  # 15 cm back along approach vector after grasp

# Examples, need to get actual positions
NAMED_POSE_COORDS = {
    'attention': {'x': 0.8644, 'y': 0.6048, 'z': 0.8177, 'roll': 0.-1.7748, 'pitch': -1.5708, 'yaw': 0.2043},
    'crouch':    {'x': 0.7553, 'y': 0.0930, 'z': 0.3605, 'roll': 0.-2.4707, 'pitch': -0.0085, 'yaw': 0.0193},
    'bin':       {'x': 0.8094, 'y': -1.1524, 'z': 0.2916, 'roll': 0.-3.1414, 'pitch': 0.0003, 'yaw': 3.141688},
}

class TomatoPicker(Node):

    def __init__(self):

        super().__init__('tomato_picker')

        # -------- Members --------
        self.tf_buffer   = Buffer()                                # TF2 buffer to store transforms
        self.tf_listener = TransformListener(self.tf_buffer, self) # TF2 listener to populate the buffer with transforms from the TF tree

        self.safe_to_pick = True
        self.picked_ids   = set()

        self.poses_list: list = [] # Latest computed batch of pose coordinates

        # -------- Subscribers --------
        self.create_subscription(Bool, '/agrobot/safe_to_pick', self.safety_callback, 10)      # Safety gate subscriber: listens to Node 1's assessment of whether it's currently safe to pick. If False, the main picking callback will ignore incoming detections until it turns True again
        self.create_subscription(String, '/agrobot/tomato_spatial', self.spatial_callback, 10) # Main detection subscriber: listens to spatial detections from Node 2 as JSON string, triggers the main picking logic in spatial_callback

        # -------- Publishers --------
        self.publisher_ = self.create_publisher(PoseArray, '/agrobot/pick_targets', 10) # PoseArray of pick targets for MoveIt, published after processing each detection batch. Each Pose's position is a pick waypoint and orientation encodes the gripper approach direction

        # -------- Services --------
        self.create_service(GetPoses, '/agrobot/get_coords', self.get_poses_callback)


        self.get_logger().info('TomatoPicker ready, waiting for detections...')

    # ------------------------------------------------------------------
    # Safety gate callback: updates safe_to_pick state based on Node 1's assessment of robot safety
    # ------------------------------------------------------------------
    def safety_callback(self, msg: Bool):

        self.safe_to_pick = msg.data # Update the persistent safety flag based on incoming message

        # Log any time we enter an unsafe state, but don't log every time we receive detections while unsafe to avoid spamming the logs
        if not self.safe_to_pick:
            self.get_logger().warn('safe_to_pick is False — picking paused')

    # ------------------------------------------------------------------
    # Get poses service callback: returns the latest computed list of pick poses for MoveIt as a JSON string
    # ------------------------------------------------------------------
    def get_poses_callback(self, request, response):

        if not self.poses_list:
            response.success = False
            response.message = 'No poses available yet'
            response.poses_json = '[]'

        else:
            response.success = True
            response.message = f'Returning {len(self.poses_list)} tomato(es) pick poses as JSON'
            response.poses_json = json.dumps(self.poses_list)

        return response

    # ------------------------------------------------------------------
    # Main callback: fires every time Node 2 publishes a detection batch
    # ------------------------------------------------------------------
    def spatial_callback(self, msg: String):

        # Safety gate check: if it's currently not safe to pick, ignore this batch of detections entirely and wait for the next one
        # This prevents us from queuing up a bunch of pick targets while the robot is in an unsafe state, which could lead to a backlog of targets that all get published at once when we become safe again
        if not self.safe_to_pick:
            self.get_logger().warn('Received detections but safe_to_pick = False, skipping')
            return

        # Parse the incoming JSON string into a list of tomato detections. Each detection is expected to have a unique tomato_id, a confidence score, a centroid in camera coordinates, and a sphere radius
        try:
            tomatoes = json.loads(msg.data)
        except json.JSONDecodeError as e:
            self.get_logger().error(f'Failed to parse tomato_spatial JSON: {e}')
            return

        # Filter out low-confidence detections and ones we've already picked in previous batches
        candidates = [
            t for t in tomatoes
            if t['confidence'] >= CONFIDENCE_THRESHOLD
            and t['tomato_id'] not in self.picked_ids
        ]

        # Log how many tomatoes we have to work with after filtering, or if we have none and will skip this batch
        if not candidates:
            self.get_logger().info('No new pickable tomatoes in this batch')
            return

        # Transform centroids from camera frame -> robot base frame via TF2
        base_frame_candidates = []
        for t in candidates:
            base_pos = self.transform_to_base(t['centroid'])
            if base_pos is None:
                continue  # TF lookup failed for this tomato, skip it
            if not self.is_reachable(base_pos):
                self.get_logger().info(
                    f'Tomato {t["tomato_id"]} out of reach at '
                    f'({base_pos["x"]:.3f}, {base_pos["y"]:.3f}, {base_pos["z"]:.3f}), skipping'
                )
                continue
            base_frame_candidates.append({
                'id': t['tomato_id'],
                'pos': base_pos,
                'radius': t['sphere']['radius'],
            })

        if not base_frame_candidates:
            return
        
        self.poses_list = [] # Clear the latest poses list before building a new one for this batch

        # For each candidate tomato, compute the approach vector and build the list of poses for MoveIt, which includes approach, grasp, and retract waypoints along with the gripper orientation encoded as a quaternion. 
        # This is stored in self.poses_list as a structured dictionary
        for idx, t in enumerate(base_frame_candidates, start=1):
            approach_vec = self.approach_vector(t['pos'])
            self.poses_list.append(self.build_poses_list(t['id'], idx, t['pos'], t['radius'], approach_vec))

        # Output the list to a JSON file
        out_path = '/home/krtom/agrobot_ws/src/robot_commander/src/latest_poses.json'
        with open(out_path, 'w') as f:
            json.dump(self.poses_list, f, indent=2)
        self.get_logger().info(f'Wrote latest poses list to {out_path}')
        
        # Build the pose array for MoveIt
        pick_msg = PoseArray()
        pick_msg.header.frame_id = 'linear_rail_link'
        pick_msg.header.stamp = self.get_clock().now().to_msg()

        # For each candidate tomato, compute approach vector, waypoints, and gripper orientation, then pack them into the PoseArray message. Also mark this tomato ID as picked so we don't re-queue it in future batches
        for t in base_frame_candidates:
            approach_vec = self.approach_vector(t['pos'])
            waypoints = self.get_waypoints(t['pos'], approach_vec, t['radius'])
            quat = self.get_quaternion(approach_vec)

            for wp in waypoints:
                pose = Pose()
                pose.position.x = wp['x']
                pose.position.y = wp['y']
                pose.position.z = wp['z']
                pose.orientation.x = quat[0]
                pose.orientation.y = quat[1]
                pose.orientation.z = quat[2]
                pose.orientation.w = quat[3]
                pick_msg.poses.append(pose)

            self.picked_ids.add(t['id'])
            self.get_logger().info(f'Queued tomato {t["id"]} for picking')

        # Publish the PoseArray of pick targets for MoveIt to consume
        self.publisher_.publish(pick_msg)
        self.get_logger().info(f'Published {len(base_frame_candidates)} tomatoes to /agrobot/pick_targets')

    # ------------------------------------------------------------------
    # Coordinate transform: camera frame -> robot base frame via TF2
    # ------------------------------------------------------------------
    def transform_to_base(self, centroid: dict) -> dict | None:
        point = PointStamped()
        point.header.frame_id = 'camera_color_optical_frame'  # verify against your URDF
        point.header.stamp    = self.get_clock().now().to_msg()
        point.point.x = centroid['x']
        point.point.y = centroid['y']
        point.point.z = centroid['z']

        try:
            transformed = self.tf_buffer.transform(
                point,
                'linear_rail_link',
                timeout=rclpy.duration.Duration(seconds=0.1)
            )
            return {
                'x': transformed.point.x,
                'y': transformed.point.y,  # flip Y axis if needed based on TF results
                'z': transformed.point.z,
            }
        except (LookupException, ExtrapolationException) as e:
            self.get_logger().warn(f'TF2 transform failed: {e}')
            return None

    # ------------------------------------------------------------------
    # Reachability check (flat 3D distance from base origin)
    # ------------------------------------------------------------------
    MAX_REACH = 1.5  # meters, adjust based on the robot's actual reach

    def is_reachable(self, p: dict) -> bool:
        dist = math.sqrt(p['x']**2 + p['y']**2 + p['z']**2)
        return dist <= self.MAX_REACH

    # ------------------------------------------------------------------
    # Approach vector: arm base origin -> tomato centroid (unit vector)
    # ------------------------------------------------------------------
    def approach_vector(self, base_pos: dict) -> dict:
        mag = math.sqrt(base_pos['x']**2 + base_pos['y']**2 + base_pos['z']**2)
        return {
            'dx': base_pos['x'] / mag,
            'dy': base_pos['y'] / mag,
            'dz': base_pos['z'] / mag,
        }

    # ------------------------------------------------------------------
    # Waypoints: approach surface, grasp centroid, retract upward
    # Approach is offset by (radius + appoach standoff) along approach vector
    # so it scales with actual tomato size
    # Retract is offset by (radius + retract standoff) along the retract vector
    # ------------------------------------------------------------------
    def get_waypoints(self, centroid: dict, vec: dict, radius: float) -> list:

        approach = {
            'x': centroid['x'] - vec['dx'] * (radius + APPROACH_STANDOFF),
            'y': centroid['y'] - vec['dy'] * (radius + APPROACH_STANDOFF),
            'z': centroid['z'] - vec['dz'] * (radius + APPROACH_STANDOFF),
        }
        retract = {
            'x': centroid['x'] - vec['dx'] * (radius + RETRACT_STANDOFF),
            'y': centroid['y'] - vec['dy'] * (radius + RETRACT_STANDOFF),
            'z': centroid['z'] - vec['dz'] * (radius + RETRACT_STANDOFF),
        }
        return [approach, centroid, retract]

    # ------------------------------------------------------------------
    # Gripper orientation: rotate gripper's +Z axis to face approach vec
    # ------------------------------------------------------------------
    def get_quaternion(self, vec: dict) -> np.ndarray:
        target  = np.array([vec['dx'], vec['dy'], vec['dz']])
        current = np.array([0.0, 0.0, 1.0])  # gripper forward axis — verify in URDF
        rotation, _ = R.align_vectors([target], [current])
        return rotation.as_quat()  # [x, y, z, w]


    # ------------------------------------------------------------------
    # Convert scipy quaternion [x, y, z, w] to (roll, pitch, yaw) in radians
    # ------------------------------------------------------------------
    def quat_to_rpy(self, quat: np.ndarray) -> tuple:
        return tuple(R.from_quat(quat).as_euler('xyz'))

    # ------------------------------------------------------------------
    # Build the list of poses for MoveIt, including approach, grasp, and retract waypoints, along with the gripper orientation encoded as a quaternion
    # This is returned as a structured dictionary
    # ------------------------------------------------------------------
    def build_poses_list(self, tomato_id, tomato_index, base_pos, radius, approach_vec):

        quat = self.get_quaternion(approach_vec)
        roll, pitch, yaw = self.quat_to_rpy(quat)
        waypoints = self.get_waypoints(base_pos, approach_vec, radius)
        
        poses_list = []
        poses_list.append({'step': 'attention', 'type': 'named_pose', 'pose': NAMED_POSE_COORDS['attention']})
        poses_list.append({'step': 'crouch', 'type': 'named_pose', 'pose': NAMED_POSE_COORDS['crouch']})

        for name, waypoint in zip(['approach', 'grasp', 'retract'], waypoints):
            poses_list.append({
                'step': name,
                'type': 'waypoint',
                'pose': {
                    'x': waypoint['x'],
                    'y': waypoint['y'],
                    'z': waypoint['z'],
                    'roll': roll,
                    'pitch': pitch,
                    'yaw': yaw,
                }
            })

        poses_list.append({'step': 'bin', 'type': 'named_pose', 'pose': NAMED_POSE_COORDS['bin']})
        poses_list.append({'step': 'crouch', 'type': 'named_pose', 'pose': NAMED_POSE_COORDS['crouch']})
        
        return {'tomato_id': tomato_id, 'tomato_index': tomato_index, 'poses': poses_list}

# ----------------------------------------------------------------------

def main():
    rclpy.init()
    node = TomatoPicker()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()

