#!/usr/bin/env python3
"""Launch the Agrobot TOM v2 picking supervisor."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    args = {
        "start_position": "0.05",
        "fallback_step": "0.15",
        "min_step": "0.05",
        "max_step": "0.40",
        "overlap_factor": "0.8",
        "settle_seconds": "1.0",
        "capture_timeout": "3.0",
        "min_track_age": "2",
        "min_confidence": "0.30",
    }

    declared = [
        DeclareLaunchArgument(name, default_value=default)
        for name, default in args.items()
    ]

    supervisor = Node(
        package="agrobot_supervisor",
        executable="supervisor",
        name="agrobot_supervisor",
        output="screen",
        parameters=[{
            name: LaunchConfiguration(name) for name in args
        }],
    )

    return LaunchDescription(declared + [supervisor])
