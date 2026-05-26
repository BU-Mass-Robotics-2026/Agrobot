#!/usr/bin/env python3
"""
sim.launch.py — MoveIt simulation stack for agrobot testing.

Brings up the full stack needed for a pick sequence demo:
  - RSP, ros2_control_node (mock hardware), controller spawners, move_group, RViz
  - rail_mover, anthro_mover, cartesian_mover with kinematics loaded (required for IK)

Run the supervisor separately:
  ros2 launch agrobot_supervisor supervisor.launch.py

Usage:
  ros2 launch agrobot_supervisor sim.launch.py
  ros2 launch agrobot_supervisor sim.launch.py rviz:=false
"""

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    TimerAction,
)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    moveit_config = MoveItConfigsBuilder(
        "robot", package_name="moveit_config"
    ).to_moveit_configs()

    moveit_pkg = FindPackageShare("moveit_config")

    def moveit_launch(filename):
        return IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                PathJoinSubstitution([moveit_pkg, "launch", filename])
            )
        )

    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[
            moveit_config.robot_description,
            str(moveit_config.package_path / "config/ros2_controllers.yaml"),
        ],
        output="screen",
    )

    mover_params = [
        moveit_config.robot_description,
        moveit_config.robot_description_semantic,
        moveit_config.robot_description_kinematics,
    ]

    # Delayed so move_group is ready before MoveGroupInterface connects.
    mover_nodes = TimerAction(
        period=5.0,
        actions=[
            Node(
                package="agrobot_motion",
                executable="rail_mover",
                name="rail_mover",
                output="screen",
                parameters=mover_params,
            ),
            Node(
                package="agrobot_motion",
                executable="anthro_mover",
                name="anthro_mover",
                output="screen",
                parameters=mover_params,
            ),
            Node(
                package="agrobot_motion",
                executable="cartesian_mover",
                name="cartesian_mover",
                output="screen",
                parameters=mover_params,
            ),
        ],
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "rviz", default_value="true",
            description="Launch RViz with the MoveIt plugin"),

        ros2_control_node,
        moveit_launch("rsp.launch.py"),
        moveit_launch("static_virtual_joint_tfs.launch.py"),
        moveit_launch("move_group.launch.py"),
        moveit_launch("spawn_controllers.launch.py"),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                PathJoinSubstitution([moveit_pkg, "launch", "moveit_rviz.launch.py"])
            ),
            condition=IfCondition(LaunchConfiguration("rviz")),
        ),
        mover_nodes,
    ])
