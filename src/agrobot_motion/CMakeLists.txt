cmake_minimum_required(VERSION 3.8)
project(agrobot_motion)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Dependencies ---
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometry_msgs REQUIRED)

# --- Generate the service interfaces ---
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/RailGoTo.srv"
  "srv/CartesianGoTo.srv"
  "srv/AnthroGoTo.srv"
  DEPENDENCIES geometry_msgs
)

# Typesupport target for linking same-package interfaces into the nodes.
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# --- anthro_mover node ---
add_executable(anthro_mover src/anthro_mover_node.cpp)
ament_target_dependencies(anthro_mover
  rclcpp
  moveit_ros_planning_interface
)
target_link_libraries(anthro_mover "${cpp_typesupport_target}")

# --- cartesian_mover node ---
add_executable(cartesian_mover src/cartesian_mover_node.cpp)
ament_target_dependencies(cartesian_mover
  rclcpp
  moveit_ros_planning_interface
)
target_link_libraries(cartesian_mover "${cpp_typesupport_target}")

# --- rail_mover node ---
add_executable(rail_mover src/rail_mover_node.cpp)
ament_target_dependencies(rail_mover
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)
target_link_libraries(rail_mover "${cpp_typesupport_target}")

install(TARGETS rail_mover anthro_mover cartesian_mover
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
