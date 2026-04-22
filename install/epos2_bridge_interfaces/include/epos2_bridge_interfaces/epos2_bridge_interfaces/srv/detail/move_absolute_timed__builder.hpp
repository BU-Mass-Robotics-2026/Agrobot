// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from epos2_bridge_interfaces:srv/MoveAbsoluteTimed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "epos2_bridge_interfaces/srv/move_absolute_timed.hpp"


#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__BUILDER_HPP_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace epos2_bridge_interfaces
{

namespace srv
{

namespace builder
{

class Init_MoveAbsoluteTimed_Request_duration_sec
{
public:
  explicit Init_MoveAbsoluteTimed_Request_duration_sec(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request & msg)
  : msg_(msg)
  {}
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request duration_sec(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request::_duration_sec_type arg)
  {
    msg_.duration_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request msg_;
};

class Init_MoveAbsoluteTimed_Request_target_rad
{
public:
  Init_MoveAbsoluteTimed_Request_target_rad()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveAbsoluteTimed_Request_duration_sec target_rad(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request::_target_rad_type arg)
  {
    msg_.target_rad = std::move(arg);
    return Init_MoveAbsoluteTimed_Request_duration_sec(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request>()
{
  return epos2_bridge_interfaces::srv::builder::Init_MoveAbsoluteTimed_Request_target_rad();
}

}  // namespace epos2_bridge_interfaces


namespace epos2_bridge_interfaces
{

namespace srv
{

namespace builder
{

class Init_MoveAbsoluteTimed_Response_message
{
public:
  explicit Init_MoveAbsoluteTimed_Response_message(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response & msg)
  : msg_(msg)
  {}
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response message(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response msg_;
};

class Init_MoveAbsoluteTimed_Response_success
{
public:
  Init_MoveAbsoluteTimed_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveAbsoluteTimed_Response_message success(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveAbsoluteTimed_Response_message(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response>()
{
  return epos2_bridge_interfaces::srv::builder::Init_MoveAbsoluteTimed_Response_success();
}

}  // namespace epos2_bridge_interfaces


namespace epos2_bridge_interfaces
{

namespace srv
{

namespace builder
{

class Init_MoveAbsoluteTimed_Event_response
{
public:
  explicit Init_MoveAbsoluteTimed_Event_response(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & msg)
  : msg_(msg)
  {}
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event response(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event msg_;
};

class Init_MoveAbsoluteTimed_Event_request
{
public:
  explicit Init_MoveAbsoluteTimed_Event_request(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event & msg)
  : msg_(msg)
  {}
  Init_MoveAbsoluteTimed_Event_response request(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MoveAbsoluteTimed_Event_response(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event msg_;
};

class Init_MoveAbsoluteTimed_Event_info
{
public:
  Init_MoveAbsoluteTimed_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveAbsoluteTimed_Event_request info(::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MoveAbsoluteTimed_Event_request(msg_);
  }

private:
  ::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event>()
{
  return epos2_bridge_interfaces::srv::builder::Init_MoveAbsoluteTimed_Event_info();
}

}  // namespace epos2_bridge_interfaces

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__BUILDER_HPP_
