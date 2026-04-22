cmake_minimum_required(VERSION 3.8)
project(robot_commander)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

add_executable(named_goal src/tests/named_goal.cpp)
ament_target_dependencies(named_goal rclcpp moveit_ros_planning_interface)

add_executable(joint_goal src/tests/joint_goal.cpp)
ament_target_dependencies(joint_goal rclcpp moveit_ros_planning_interface)

add_executable(pose_goal src/tests/pose_goal.cpp)
ament_target_dependencies(pose_goal rclcpp moveit_ros_planning_interface)

install(TARGETS
  named_goal
  joint_goal
  pose_goal
  DESTINATION lib/${PROJECT_NAME})

ament_package()
