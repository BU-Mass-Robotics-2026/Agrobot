import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, LogInfo
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg_share = get_package_share_directory("epos2_bridge")
    can_interface = LaunchConfiguration("can_interface")

    bus_config = os.path.join(pkg_share, "config", "canopen", "bus_epos2_j2_j6.yml")
    master_config = os.path.join(pkg_share, "config", "canopen", "master_epos2_j2_j6.dcf")

    return LaunchDescription([
        DeclareLaunchArgument("can_interface", default_value="can0"),
        LogInfo(msg=bus_config),
        LogInfo(msg=master_config),
        LogInfo(msg=can_interface),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                FindPackageShare("canopen_core"),
                "/launch/canopen.launch.py",
            ]),
            launch_arguments={
                "master_config": master_config,
                "bus_config": bus_config,
                "can_interface_name": can_interface,
            }.items(),
        ),
    ])
