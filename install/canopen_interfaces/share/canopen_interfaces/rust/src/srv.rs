#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to canopen_interfaces__srv__COHeartbeatID_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COHeartbeatID_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: u8,

    /// ms
    pub heartbeat: u16,

}



impl Default for COHeartbeatID_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COHeartbeatID_Request::default())
  }
}

impl rosidl_runtime_rs::Message for COHeartbeatID_Request {
  type RmwMsg = super::srv::rmw::COHeartbeatID_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        nodeid: msg.nodeid,
        heartbeat: msg.heartbeat,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      nodeid: msg.nodeid,
      heartbeat: msg.heartbeat,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      nodeid: msg.nodeid,
      heartbeat: msg.heartbeat,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COHeartbeatID_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COHeartbeatID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COHeartbeatID_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COHeartbeatID_Response::default())
  }
}

impl rosidl_runtime_rs::Message for COHeartbeatID_Response {
  type RmwMsg = super::srv::rmw::COHeartbeatID_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CONmtID_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONmtID_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nmtcommand: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: u8,

}



impl Default for CONmtID_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CONmtID_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CONmtID_Request {
  type RmwMsg = super::srv::rmw::CONmtID_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        nmtcommand: msg.nmtcommand,
        nodeid: msg.nodeid,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      nmtcommand: msg.nmtcommand,
      nodeid: msg.nodeid,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      nmtcommand: msg.nmtcommand,
      nodeid: msg.nodeid,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CONmtID_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONmtID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for CONmtID_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CONmtID_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CONmtID_Response {
  type RmwMsg = super::srv::rmw::CONmtID_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CORead_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CORead_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub index: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub subindex: u8,

}



impl Default for CORead_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CORead_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CORead_Request {
  type RmwMsg = super::srv::rmw::CORead_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        index: msg.index,
        subindex: msg.subindex,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      index: msg.index,
      subindex: msg.subindex,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      index: msg.index,
      subindex: msg.subindex,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CORead_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CORead_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: u32,

}



impl Default for CORead_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CORead_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CORead_Response {
  type RmwMsg = super::srv::rmw::CORead_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        data: msg.data,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      data: msg.data,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      data: msg.data,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COReadID_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COReadID_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub index: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub subindex: u8,

    /// 8 = uint8_t, 16 = uint16_t, 32 = uint32_t
    pub canopen_datatype: u8,

}

impl COReadID_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT8: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT16: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT32: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT8: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT16: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT32: u8 = 7;

}


impl Default for COReadID_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COReadID_Request::default())
  }
}

impl rosidl_runtime_rs::Message for COReadID_Request {
  type RmwMsg = super::srv::rmw::COReadID_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        nodeid: msg.nodeid,
        index: msg.index,
        subindex: msg.subindex,
        canopen_datatype: msg.canopen_datatype,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      nodeid: msg.nodeid,
      index: msg.index,
      subindex: msg.subindex,
      canopen_datatype: msg.canopen_datatype,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      nodeid: msg.nodeid,
      index: msg.index,
      subindex: msg.subindex,
      canopen_datatype: msg.canopen_datatype,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COReadID_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COReadID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: u32,

}



impl Default for COReadID_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COReadID_Response::default())
  }
}

impl rosidl_runtime_rs::Message for COReadID_Response {
  type RmwMsg = super::srv::rmw::COReadID_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        data: msg.data,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      data: msg.data,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      data: msg.data,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COWrite_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWrite_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub index: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub subindex: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: u32,

}



impl Default for COWrite_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COWrite_Request::default())
  }
}

impl rosidl_runtime_rs::Message for COWrite_Request {
  type RmwMsg = super::srv::rmw::COWrite_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        index: msg.index,
        subindex: msg.subindex,
        data: msg.data,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      index: msg.index,
      subindex: msg.subindex,
      data: msg.data,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      index: msg.index,
      subindex: msg.subindex,
      data: msg.data,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COWrite_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWrite_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COWrite_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COWrite_Response::default())
  }
}

impl rosidl_runtime_rs::Message for COWrite_Response {
  type RmwMsg = super::srv::rmw::COWrite_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COWriteID_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWriteID_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub index: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub subindex: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: u32,

    /// 8 = uint8_t, 16 = uint16_t, 32 = uint32_t
    pub canopen_datatype: u8,

}

impl COWriteID_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT8: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT16: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_INT32: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT8: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT16: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CANOPEN_DATATYPE_UINT32: u8 = 7;

}


impl Default for COWriteID_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COWriteID_Request::default())
  }
}

impl rosidl_runtime_rs::Message for COWriteID_Request {
  type RmwMsg = super::srv::rmw::COWriteID_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        nodeid: msg.nodeid,
        index: msg.index,
        subindex: msg.subindex,
        data: msg.data,
        canopen_datatype: msg.canopen_datatype,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      nodeid: msg.nodeid,
      index: msg.index,
      subindex: msg.subindex,
      data: msg.data,
      canopen_datatype: msg.canopen_datatype,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      nodeid: msg.nodeid,
      index: msg.index,
      subindex: msg.subindex,
      data: msg.data,
      canopen_datatype: msg.canopen_datatype,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COWriteID_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWriteID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COWriteID_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COWriteID_Response::default())
  }
}

impl rosidl_runtime_rs::Message for COWriteID_Response {
  type RmwMsg = super::srv::rmw::COWriteID_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COTargetDouble_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COTargetDouble_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target: f64,

}



impl Default for COTargetDouble_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COTargetDouble_Request::default())
  }
}

impl rosidl_runtime_rs::Message for COTargetDouble_Request {
  type RmwMsg = super::srv::rmw::COTargetDouble_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        target: msg.target,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      target: msg.target,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      target: msg.target,
    }
  }
}


// Corresponds to canopen_interfaces__srv__COTargetDouble_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COTargetDouble_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COTargetDouble_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::COTargetDouble_Response::default())
  }
}

impl rosidl_runtime_rs::Message for COTargetDouble_Response {
  type RmwMsg = super::srv::rmw::COTargetDouble_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CONode_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONode_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: u8,

}



impl Default for CONode_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CONode_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CONode_Request {
  type RmwMsg = super::srv::rmw::CONode_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        nodeid: msg.nodeid,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      nodeid: msg.nodeid,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      nodeid: msg.nodeid,
    }
  }
}


// Corresponds to canopen_interfaces__srv__CONode_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONode_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for CONode_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CONode_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CONode_Response {
  type RmwMsg = super::srv::rmw::CONode_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
    }
  }
}






#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COHeartbeatID() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__COHeartbeatID
#[allow(missing_docs, non_camel_case_types)]
pub struct COHeartbeatID;

impl rosidl_runtime_rs::Service for COHeartbeatID {
    type Request = COHeartbeatID_Request;
    type Response = COHeartbeatID_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COHeartbeatID() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CONmtID() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__CONmtID
#[allow(missing_docs, non_camel_case_types)]
pub struct CONmtID;

impl rosidl_runtime_rs::Service for CONmtID {
    type Request = CONmtID_Request;
    type Response = CONmtID_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CONmtID() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CORead() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__CORead
#[allow(missing_docs, non_camel_case_types)]
pub struct CORead;

impl rosidl_runtime_rs::Service for CORead {
    type Request = CORead_Request;
    type Response = CORead_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CORead() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COReadID() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__COReadID
#[allow(missing_docs, non_camel_case_types)]
pub struct COReadID;

impl rosidl_runtime_rs::Service for COReadID {
    type Request = COReadID_Request;
    type Response = COReadID_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COReadID() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COWrite() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__COWrite
#[allow(missing_docs, non_camel_case_types)]
pub struct COWrite;

impl rosidl_runtime_rs::Service for COWrite {
    type Request = COWrite_Request;
    type Response = COWrite_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COWrite() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COWriteID() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__COWriteID
#[allow(missing_docs, non_camel_case_types)]
pub struct COWriteID;

impl rosidl_runtime_rs::Service for COWriteID {
    type Request = COWriteID_Request;
    type Response = COWriteID_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COWriteID() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COTargetDouble() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__COTargetDouble
#[allow(missing_docs, non_camel_case_types)]
pub struct COTargetDouble;

impl rosidl_runtime_rs::Service for COTargetDouble {
    type Request = COTargetDouble_Request;
    type Response = COTargetDouble_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__COTargetDouble() }
    }
}




#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CONode() -> *const std::ffi::c_void;
}

// Corresponds to canopen_interfaces__srv__CONode
#[allow(missing_docs, non_camel_case_types)]
pub struct CONode;

impl rosidl_runtime_rs::Service for CONode {
    type Request = CONode_Request;
    type Response = CONode_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__canopen_interfaces__srv__CONode() }
    }
}


