// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from epos2_bridge_interfaces:srv/MoveAbsoluteTimed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "epos2_bridge_interfaces/srv/move_absolute_timed.hpp"


#ifndef EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__STRUCT_HPP_
#define EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request __attribute__((deprecated))
#else
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request __declspec(deprecated)
#endif

namespace epos2_bridge_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveAbsoluteTimed_Request_
{
  using Type = MoveAbsoluteTimed_Request_<ContainerAllocator>;

  explicit MoveAbsoluteTimed_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_rad = 0.0;
      this->duration_sec = 0.0;
    }
  }

  explicit MoveAbsoluteTimed_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_rad = 0.0;
      this->duration_sec = 0.0;
    }
  }

  // field types and members
  using _target_rad_type =
    double;
  _target_rad_type target_rad;
  using _duration_sec_type =
    double;
  _duration_sec_type duration_sec;

  // setters for named parameter idiom
  Type & set__target_rad(
    const double & _arg)
  {
    this->target_rad = _arg;
    return *this;
  }
  Type & set__duration_sec(
    const double & _arg)
  {
    this->duration_sec = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveAbsoluteTimed_Request_ & other) const
  {
    if (this->target_rad != other.target_rad) {
      return false;
    }
    if (this->duration_sec != other.duration_sec) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveAbsoluteTimed_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveAbsoluteTimed_Request_

// alias to use template instance with default allocator
using MoveAbsoluteTimed_Request =
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace epos2_bridge_interfaces


#ifndef _WIN32
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response __attribute__((deprecated))
#else
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response __declspec(deprecated)
#endif

namespace epos2_bridge_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveAbsoluteTimed_Response_
{
  using Type = MoveAbsoluteTimed_Response_<ContainerAllocator>;

  explicit MoveAbsoluteTimed_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit MoveAbsoluteTimed_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveAbsoluteTimed_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveAbsoluteTimed_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveAbsoluteTimed_Response_

// alias to use template instance with default allocator
using MoveAbsoluteTimed_Response =
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace epos2_bridge_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event __attribute__((deprecated))
#else
# define DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event __declspec(deprecated)
#endif

namespace epos2_bridge_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveAbsoluteTimed_Event_
{
  using Type = MoveAbsoluteTimed_Event_<ContainerAllocator>;

  explicit MoveAbsoluteTimed_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit MoveAbsoluteTimed_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event
    std::shared_ptr<epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveAbsoluteTimed_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveAbsoluteTimed_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveAbsoluteTimed_Event_

// alias to use template instance with default allocator
using MoveAbsoluteTimed_Event =
  epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace epos2_bridge_interfaces

namespace epos2_bridge_interfaces
{

namespace srv
{

struct MoveAbsoluteTimed
{
  using Request = epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Request;
  using Response = epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Response;
  using Event = epos2_bridge_interfaces::srv::MoveAbsoluteTimed_Event;
};

}  // namespace srv

}  // namespace epos2_bridge_interfaces

#endif  // EPOS2_BRIDGE_INTERFACES__SRV__DETAIL__MOVE_ABSOLUTE_TIMED__STRUCT_HPP_
