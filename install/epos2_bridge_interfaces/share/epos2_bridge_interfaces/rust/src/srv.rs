#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to epos2_bridge_interfaces__srv__MoveDelta_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveDelta_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub delta_rad: f64,

}



impl Default for MoveDelta_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveDelta_Request::default())
  }
}

impl rosidl_runtime_rs::Message for MoveDelta_Request {
  type RmwMsg = super::srv::rmw::MoveDelta_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        delta_rad: msg.delta_rad,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      delta_rad: msg.delta_rad,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      delta_rad: msg.delta_rad,
    }
  }
}


// Corresponds to epos2_bridge_interfaces__srv__MoveDelta_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveDelta_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for MoveDelta_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveDelta_Response::default())
  }
}

impl rosidl_runtime_rs::Message for MoveDelta_Response {
  type RmwMsg = super::srv::rmw::MoveDelta_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to epos2_bridge_interfaces__srv__MoveAbsolute_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsolute_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_rad: f64,

}



impl Default for MoveAbsolute_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveAbsolute_Request::default())
  }
}

impl rosidl_runtime_rs::Message for MoveAbsolute_Request {
  type RmwMsg = super::srv::rmw::MoveAbsolute_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        target_rad: msg.target_rad,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      target_rad: msg.target_rad,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      target_rad: msg.target_rad,
    }
  }
}


// Corresponds to epos2_bridge_interfaces__srv__MoveAbsolute_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsolute_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for MoveAbsolute_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveAbsolute_Response::default())
  }
}

impl rosidl_runtime_rs::Message for MoveAbsolute_Response {
  type RmwMsg = super::srv::rmw::MoveAbsolute_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsoluteTimed_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_rad: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub duration_sec: f64,

}



impl Default for MoveAbsoluteTimed_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveAbsoluteTimed_Request::default())
  }
}

impl rosidl_runtime_rs::Message for MoveAbsoluteTimed_Request {
  type RmwMsg = super::srv::rmw::MoveAbsoluteTimed_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        target_rad: msg.target_rad,
        duration_sec: msg.duration_sec,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      target_rad: msg.target_rad,
      duration_sec: msg.duration_sec,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      target_rad: msg.target_rad,
      duration_sec: msg.duration_sec,
    }
  }
}


// Corresponds to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsoluteTimed_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for MoveAbsoluteTimed_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::MoveAbsoluteTimed_Response::default())
  }
}

impl rosidl_runtime_rs::Message for MoveAbsoluteTimed_Response {
  type RmwMsg = super::srv::rmw::MoveAbsoluteTimed_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}






#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta() -> *const std::ffi::c_void;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveDelta
#[allow(missing_docs, non_camel_case_types)]
pub struct MoveDelta;

impl rosidl_runtime_rs::Service for MoveDelta {
    type Request = MoveDelta_Request;
    type Response = MoveDelta_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta() }
    }
}




#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute() -> *const std::ffi::c_void;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsolute
#[allow(missing_docs, non_camel_case_types)]
pub struct MoveAbsolute;

impl rosidl_runtime_rs::Service for MoveAbsolute {
    type Request = MoveAbsolute_Request;
    type Response = MoveAbsolute_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute() }
    }
}




#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed() -> *const std::ffi::c_void;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsoluteTimed
#[allow(missing_docs, non_camel_case_types)]
pub struct MoveAbsoluteTimed;

impl rosidl_runtime_rs::Service for MoveAbsoluteTimed {
    type Request = MoveAbsoluteTimed_Request;
    type Response = MoveAbsoluteTimed_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed() }
    }
}


