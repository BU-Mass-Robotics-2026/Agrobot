// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from epos2_bridge_interfaces:srv/MoveAbsolute.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "epos2_bridge_interfaces/srv/move_absolute.h"


#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TYPE_SUPPORT_H_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "epos2_bridge_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  epos2_bridge_interfaces,
  srv,
  MoveAbsolute
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TYPE_SUPPORT_H_
