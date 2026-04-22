// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from epos2_bridge_interfaces:srv/MoveAbsolute.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "epos2_bridge_interfaces/srv/move_absolute.hpp"


#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TRAITS_HPP_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "epos2_bridge_interfaces/srv/detail/move_absolute__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace epos2_bridge_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveAbsolute_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: target_rad
  {
    out << "target_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.target_rad, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveAbsolute_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.target_rad, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveAbsolute_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace epos2_bridge_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use epos2_bridge_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const epos2_bridge_interfaces::srv::MoveAbsolute_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  epos2_bridge_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use epos2_bridge_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const epos2_bridge_interfaces::srv::MoveAbsolute_Request & msg)
{
  return epos2_bridge_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<epos2_bridge_interfaces::srv::MoveAbsolute_Request>()
{
  return "epos2_bridge_interfaces::srv::MoveAbsolute_Request";
}

template<>
inline const char * name<epos2_bridge_interfaces::srv::MoveAbsolute_Request>()
{
  return "epos2_bridge_interfaces/srv/MoveAbsolute_Request";
}

template<>
struct has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<epos2_bridge_interfaces::srv::MoveAbsolute_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace epos2_bridge_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveAbsolute_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveAbsolute_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveAbsolute_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace epos2_bridge_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use epos2_bridge_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const epos2_bridge_interfaces::srv::MoveAbsolute_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  epos2_bridge_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use epos2_bridge_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const epos2_bridge_interfaces::srv::MoveAbsolute_Response & msg)
{
  return epos2_bridge_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<epos2_bridge_interfaces::srv::MoveAbsolute_Response>()
{
  return "epos2_bridge_interfaces::srv::MoveAbsolute_Response";
}

template<>
inline const char * name<epos2_bridge_interfaces::srv::MoveAbsolute_Response>()
{
  return "epos2_bridge_interfaces/srv/MoveAbsolute_Response";
}

template<>
struct has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<epos2_bridge_interfaces::srv::MoveAbsolute_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace epos2_bridge_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveAbsolute_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveAbsolute_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveAbsolute_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace epos2_bridge_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use epos2_bridge_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const epos2_bridge_interfaces::srv::MoveAbsolute_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  epos2_bridge_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use epos2_bridge_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const epos2_bridge_interfaces::srv::MoveAbsolute_Event & msg)
{
  return epos2_bridge_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<epos2_bridge_interfaces::srv::MoveAbsolute_Event>()
{
  return "epos2_bridge_interfaces::srv::MoveAbsolute_Event";
}

template<>
inline const char * name<epos2_bridge_interfaces::srv::MoveAbsolute_Event>()
{
  return "epos2_bridge_interfaces/srv/MoveAbsolute_Event";
}

template<>
struct has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Event>
  : std::integral_constant<bool, has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Request>::value && has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<epos2_bridge_interfaces::srv::MoveAbsolute_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<epos2_bridge_interfaces::srv::MoveAbsolute>()
{
  return "epos2_bridge_interfaces::srv::MoveAbsolute";
}

template<>
inline const char * name<epos2_bridge_interfaces::srv::MoveAbsolute>()
{
  return "epos2_bridge_interfaces/srv/MoveAbsolute";
}

template<>
struct has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute>
  : std::integral_constant<
    bool,
    has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute_Request>::value &&
    has_fixed_size<epos2_bridge_interfaces::srv::MoveAbsolute_Response>::value
  >
{
};

template<>
struct has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute>
  : std::integral_constant<
    bool,
    has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Request>::value &&
    has_bounded_size<epos2_bridge_interfaces::srv::MoveAbsolute_Response>::value
  >
{
};

template<>
struct is_service<epos2_bridge_interfaces::srv::MoveAbsolute>
  : std::true_type
{
};

template<>
struct is_service_request<epos2_bridge_interfaces::srv::MoveAbsolute_Request>
  : std::true_type
{
};

template<>
struct is_service_response<epos2_bridge_interfaces::srv::MoveAbsolute_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE__TRAITS_HPP_
