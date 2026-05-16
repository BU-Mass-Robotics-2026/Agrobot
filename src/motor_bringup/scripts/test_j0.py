#!/usr/bin/env python3
"""
j0 test tool — two modes:

  action (default): sends FollowJointTrajectory to arm_controller, exercises the full stack.
  forward:          publishes directly to forward_position_controller (bypasses trajectory
                    interpolation — good for checking direction and encoder counts).

Usage:
  ros2 run motor_bringup test_j0.py --target 0.02
  ros2 run motor_bringup test_j0.py --mode forward --target 0.02
  ros2 run motor_bringup test_j0.py --mode forward --target 0.0   # back to home
"""

import argparse
import sys
import time

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from control_msgs.action import FollowJointTrajectory
from std_msgs.msg import Float64MultiArray
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration


ALL_JOINTS = ["joint0", "joint1", "joint2", "joint3", "joint4", "joint5", "joint6"]
J0_INDEX = 0


class J0Tester(Node):
    def __init__(self, mode: str, target: float, duration_sec: float):
        super().__init__("j0_tester")
        self._mode = mode
        self._target = target
        self._duration_sec = duration_sec
        self._done = False

        if mode == "forward":
            self._pub = self.create_publisher(
                Float64MultiArray, "/forward_position_controller/commands", 1
            )
            # Give the publisher time to connect
            self.create_timer(0.5, self._send_forward)
        else:
            self._action_client = ActionClient(
                self, FollowJointTrajectory, "/arm_controller/follow_joint_trajectory"
            )
            self.create_timer(0.1, self._send_action)

    def _send_forward(self):
        msg = Float64MultiArray()
        msg.data = [float(self._target)]
        self._pub.publish(msg)
        self.get_logger().info(f"Published forward command: joint0 → {self._target:.4f} m")
        self._done = True

    def _send_action(self):
        if not self._action_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error("arm_controller action server not available")
            self._done = True
            return

        goal = FollowJointTrajectory.Goal()
        traj = JointTrajectory()
        traj.joint_names = ALL_JOINTS

        point = JointTrajectoryPoint()
        point.positions = [self._target] + [0.0] * (len(ALL_JOINTS) - 1)
        point.time_from_start = Duration(
            sec=int(self._duration_sec),
            nanosec=int((self._duration_sec % 1) * 1e9),
        )
        traj.points = [point]
        goal.trajectory = traj

        self.get_logger().info(
            f"Sending goal: joint0 → {self._target:.4f} m over {self._duration_sec:.1f}s"
        )
        future = self._action_client.send_goal_async(goal)
        future.add_done_callback(self._goal_response_cb)

    def _goal_response_cb(self, future):
        handle = future.result()
        if not handle.accepted:
            self.get_logger().error("Goal rejected by arm_controller")
            self._done = True
            return
        self.get_logger().info("Goal accepted — waiting for result...")
        handle.get_result_async().add_done_callback(self._result_cb)

    def _result_cb(self, future):
        result = future.result().result
        status = future.result().status
        from action_msgs.msg import GoalStatus
        if status == GoalStatus.STATUS_SUCCEEDED:
            self.get_logger().info("SUCCEEDED")
        else:
            self.get_logger().error(f"FAILED — status={status}, error_code={result.error_code}")
        self._done = True


def main():
    parser = argparse.ArgumentParser(description="Test j0 motion")
    parser.add_argument("--mode", choices=["action", "forward"], default="action")
    parser.add_argument("--target", type=float, default=0.02,
                        help="Target position in metres (default: 0.02)")
    parser.add_argument("--duration", type=float, default=3.0,
                        help="Trajectory duration in seconds, action mode only (default: 3.0)")
    args, ros_args = parser.parse_known_args()

    rclpy.init(args=ros_args)
    node = J0Tester(args.mode, args.target, args.duration)

    while rclpy.ok() and not node._done:
        rclpy.spin_once(node, timeout_sec=0.1)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
