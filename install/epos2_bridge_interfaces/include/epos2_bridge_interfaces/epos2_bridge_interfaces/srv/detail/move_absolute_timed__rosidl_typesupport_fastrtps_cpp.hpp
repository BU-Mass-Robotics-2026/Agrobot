// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from epos2_bridge_interfaces:srv/MoveAbsoluteTimed.idl
// generated code does not contain a copyright notice

#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "epos2_bridge_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace epos2_bridge_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_MoveAbsoluteTimed_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_key_MoveAbsoluteTimed_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace epos2_bridge_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, epos2_bridge_interfaces, srv, MoveAbsoluteTimed_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "epos2_bridge_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace epos2_bridge_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_MoveAbsoluteTimed_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_key_MoveAbsoluteTimed_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace epos2_bridge_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, epos2_bridge_interfaces, srv, MoveAbsoluteTimed_Response)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "epos2_bridge_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace epos2_bridge_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_MoveAbsoluteTimed_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
cdr_serialize_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
get_serialized_size_key(
  const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
max_serialized_size_key_MoveAbsoluteTimed_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace epos2_bridge_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, epos2_bridge_interfaces, srv, MoveAbsoluteTimed_Event)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "epos2_bridge_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_epos2_bridge_interfaces
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, epos2_bridge_interfaces, srv, MoveAbsoluteTimed)();

#ifdef __cplusplus
}
#endif

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
