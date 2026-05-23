"""Launch the Copley bridge for joint 0 (APZ-090-50, CAN node 1)."""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    config = os.path.join(
        get_package_share_directory("copley_bridge"),
        "config",
        "copley_j0.yaml",
    )

    return LaunchDescription([
        Node(
            package="copley_bridge",
            executable="copley_joint_bridge",
            name="copley_j0_bridge",
            output="screen",
            parameters=[config],
            remappings=[
                ("fault", "/copley/j0/fault"),
                ("reduced_traj", "/copley/j0/reduced_traj"),
                ("clear_fault", "/copley/j0/clear_fault"),
                ("arm_ipm", "/copley/j0/arm_ipm"),
                ("disarm_ipm", "/copley/j0/disarm_ipm"),
                ("move_absolute_timed", "/copley/j0/move_absolute_timed"),
            ],
        )
    ])
