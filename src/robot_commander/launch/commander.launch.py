from moveit_configs_utils import MoveItConfigsBuilder
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    moveit_config = MoveItConfigsBuilder("robot", package_name="moveit_config").to_moveit_configs()

    commander_node = Node(
        package="robot_commander",
        executable="commander",
        parameters=[moveit_config.to_dict()],
    )
    
    tomato_picker_node = Node(
        package="robot_commander",
        executable="tomato_picker.py",
    )

    return LaunchDescription([
        commander_node,
        tomato_picker_node,
    ])
