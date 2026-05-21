"""Launch the Copley bridge for joint 1 (APZ-090-50, CAN node 2)."""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    config = os.path.join(
        get_package_share_directory("copley_bridge"),
        "config",
        "copley_j1.yaml",
    )

    return LaunchDescription([
        Node(
            package="copley_bridge",
            executable="copley_joint_bridge",
            name="copley_j1_bridge",
            output="screen",
            parameters=[config],
            remappings=[
                ("fault", "/copley/j1/fault"),
                ("reduced_traj", "/copley/j1/reduced_traj"),
                ("clear_fault", "/copley/j1/clear_fault"),
                ("arm_ipm", "/copley/j1/arm_ipm"),
                ("disarm_ipm", "/copley/j1/disarm_ipm"),
                ("move_absolute_timed", "/copley/j1/move_absolute_timed"),
            ],
        )
    ])
