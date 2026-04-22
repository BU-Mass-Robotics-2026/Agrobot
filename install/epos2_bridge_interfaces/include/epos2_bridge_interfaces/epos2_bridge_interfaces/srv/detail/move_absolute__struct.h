// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from epos2_bridge_interfaces:srv/MoveAbsolute.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "epos2_bridge_interfaces/srv/move_absolute.h"


#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__STRUCT_H_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/MoveAbsolute in the package epos2_bridge_interfaces.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Request
{
  double target_rad;
} epos2_bridge_interfaces__srv__MoveAbsolute_Request;

// Struct for a sequence of epos2_bridge_interfaces__srv__MoveAbsolute_Request.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence
{
  epos2_bridge_interfaces__srv__MoveAbsolute_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveAbsolute in the package epos2_bridge_interfaces.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Response
{
  bool success;
  rosidl_runtime_c__String message;
} epos2_bridge_interfaces__srv__MoveAbsolute_Response;

// Struct for a sequence of epos2_bridge_interfaces__srv__MoveAbsolute_Response.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence
{
  epos2_bridge_interfaces__srv__MoveAbsolute_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  epos2_bridge_interfaces__srv__MoveAbsolute_Event__request__MAX_SIZE = 1
};
// response
enum
{
  epos2_bridge_interfaces__srv__MoveAbsolute_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/MoveAbsolute in the package epos2_bridge_interfaces.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Event
{
  service_msgs__msg__ServiceEventInfo info;
  epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence request;
  epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence response;
} epos2_bridge_interfaces__srv__MoveAbsolute_Event;

// Struct for a sequence of epos2_bridge_interfaces__srv__MoveAbsolute_Event.
typedef struct epos2_bridge_interfaces__srv__MoveAbsolute_Event__Sequence
{
  epos2_bridge_interfaces__srv__MoveAbsolute_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} epos2_bridge_interfaces__srv__MoveAbsolute_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__STRUCT_H_
