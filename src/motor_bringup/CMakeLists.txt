cmake_minimum_required(VERSION 3.8)
project(motor_bringup)

find_package(ament_cmake REQUIRED)
find_package(lely_core_libraries REQUIRED)

# Generate master DCF from bus.yml + EDS at build time.
# Requires: config/j0/everest_evs_xcr_c.eds (get from Ingenia support).
cogen_dcf(j0)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

# cogen_dcf installs config/j0/ itself; install the xacro/urdf configs separately
install(FILES
  config/robot.ros2_control.hardware.xacro
  config/robot.hardware.urdf.xacro
  DESTINATION share/${PROJECT_NAME}/config
)

install(PROGRAMS
  scripts/test_j0.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
