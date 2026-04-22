#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COHeartbeatID_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COHeartbeatID_Request__init(msg: *mut COHeartbeatID_Request) -> bool;
    fn canopen_interfaces__srv__COHeartbeatID_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__COHeartbeatID_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Request>);
    fn canopen_interfaces__srv__COHeartbeatID_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COHeartbeatID_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COHeartbeatID_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COHeartbeatID_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COHeartbeatID_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COHeartbeatID_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COHeartbeatID_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COHeartbeatID_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COHeartbeatID_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COHeartbeatID_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COHeartbeatID_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COHeartbeatID_Response__init(msg: *mut COHeartbeatID_Response) -> bool;
    fn canopen_interfaces__srv__COHeartbeatID_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__COHeartbeatID_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Response>);
    fn canopen_interfaces__srv__COHeartbeatID_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COHeartbeatID_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<COHeartbeatID_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COHeartbeatID_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COHeartbeatID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COHeartbeatID_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COHeartbeatID_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COHeartbeatID_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COHeartbeatID_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COHeartbeatID_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COHeartbeatID_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COHeartbeatID_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COHeartbeatID_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COHeartbeatID_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONmtID_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CONmtID_Request__init(msg: *mut CONmtID_Request) -> bool;
    fn canopen_interfaces__srv__CONmtID_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__CONmtID_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Request>);
    fn canopen_interfaces__srv__CONmtID_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CONmtID_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CONmtID_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CONmtID_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CONmtID_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CONmtID_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CONmtID_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CONmtID_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CONmtID_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONmtID_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONmtID_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CONmtID_Response__init(msg: *mut CONmtID_Response) -> bool;
    fn canopen_interfaces__srv__CONmtID_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__CONmtID_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Response>);
    fn canopen_interfaces__srv__CONmtID_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CONmtID_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CONmtID_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CONmtID_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONmtID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for CONmtID_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CONmtID_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CONmtID_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CONmtID_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONmtID_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CONmtID_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CONmtID_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CONmtID_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONmtID_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CORead_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CORead_Request__init(msg: *mut CORead_Request) -> bool;
    fn canopen_interfaces__srv__CORead_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CORead_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__CORead_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CORead_Request>);
    fn canopen_interfaces__srv__CORead_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CORead_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CORead_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CORead_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CORead_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CORead_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CORead_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CORead_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CORead_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CORead_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CORead_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CORead_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CORead_Response__init(msg: *mut CORead_Response) -> bool;
    fn canopen_interfaces__srv__CORead_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CORead_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__CORead_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CORead_Response>);
    fn canopen_interfaces__srv__CORead_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CORead_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CORead_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CORead_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CORead_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CORead_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CORead_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CORead_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CORead_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CORead_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CORead_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CORead_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COReadID_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COReadID_Request__init(msg: *mut COReadID_Request) -> bool;
    fn canopen_interfaces__srv__COReadID_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COReadID_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__COReadID_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COReadID_Request>);
    fn canopen_interfaces__srv__COReadID_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COReadID_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<COReadID_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COReadID_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COReadID_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COReadID_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COReadID_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COReadID_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COReadID_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COReadID_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COReadID_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COReadID_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COReadID_Response__init(msg: *mut COReadID_Response) -> bool;
    fn canopen_interfaces__srv__COReadID_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COReadID_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__COReadID_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COReadID_Response>);
    fn canopen_interfaces__srv__COReadID_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COReadID_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<COReadID_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COReadID_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COReadID_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COReadID_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COReadID_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COReadID_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COReadID_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COReadID_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COReadID_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COReadID_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWrite_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COWrite_Request__init(msg: *mut COWrite_Request) -> bool;
    fn canopen_interfaces__srv__COWrite_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COWrite_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__COWrite_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COWrite_Request>);
    fn canopen_interfaces__srv__COWrite_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COWrite_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<COWrite_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COWrite_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COWrite_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COWrite_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COWrite_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COWrite_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COWrite_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COWrite_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWrite_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWrite_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COWrite_Response__init(msg: *mut COWrite_Response) -> bool;
    fn canopen_interfaces__srv__COWrite_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COWrite_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__COWrite_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COWrite_Response>);
    fn canopen_interfaces__srv__COWrite_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COWrite_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<COWrite_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COWrite_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWrite_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COWrite_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COWrite_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COWrite_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COWrite_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWrite_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COWrite_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COWrite_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COWrite_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWrite_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWriteID_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COWriteID_Request__init(msg: *mut COWriteID_Request) -> bool;
    fn canopen_interfaces__srv__COWriteID_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__COWriteID_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Request>);
    fn canopen_interfaces__srv__COWriteID_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COWriteID_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COWriteID_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COWriteID_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COWriteID_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COWriteID_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COWriteID_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COWriteID_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COWriteID_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWriteID_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWriteID_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COWriteID_Response__init(msg: *mut COWriteID_Response) -> bool;
    fn canopen_interfaces__srv__COWriteID_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__COWriteID_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Response>);
    fn canopen_interfaces__srv__COWriteID_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COWriteID_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<COWriteID_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COWriteID_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COWriteID_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COWriteID_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COWriteID_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COWriteID_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COWriteID_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COWriteID_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COWriteID_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COWriteID_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COWriteID_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COWriteID_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COTargetDouble_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COTargetDouble_Request__init(msg: *mut COTargetDouble_Request) -> bool;
    fn canopen_interfaces__srv__COTargetDouble_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__COTargetDouble_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Request>);
    fn canopen_interfaces__srv__COTargetDouble_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COTargetDouble_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COTargetDouble_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COTargetDouble_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target: f64,

}



impl Default for COTargetDouble_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COTargetDouble_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COTargetDouble_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COTargetDouble_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COTargetDouble_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COTargetDouble_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COTargetDouble_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COTargetDouble_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COTargetDouble_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__COTargetDouble_Response__init(msg: *mut COTargetDouble_Response) -> bool;
    fn canopen_interfaces__srv__COTargetDouble_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__COTargetDouble_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Response>);
    fn canopen_interfaces__srv__COTargetDouble_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COTargetDouble_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<COTargetDouble_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__COTargetDouble_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COTargetDouble_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for COTargetDouble_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__COTargetDouble_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__COTargetDouble_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COTargetDouble_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__COTargetDouble_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COTargetDouble_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COTargetDouble_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/COTargetDouble_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__COTargetDouble_Response() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONode_Request() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CONode_Request__init(msg: *mut CONode_Request) -> bool;
    fn canopen_interfaces__srv__CONode_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CONode_Request>, size: usize) -> bool;
    fn canopen_interfaces__srv__CONode_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CONode_Request>);
    fn canopen_interfaces__srv__CONode_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CONode_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CONode_Request>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CONode_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONode_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub nodeid: u8,

}



impl Default for CONode_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CONode_Request__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CONode_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CONode_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CONode_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CONode_Request where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CONode_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONode_Request() }
  }
}


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONode_Response() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__srv__CONode_Response__init(msg: *mut CONode_Response) -> bool;
    fn canopen_interfaces__srv__CONode_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CONode_Response>, size: usize) -> bool;
    fn canopen_interfaces__srv__CONode_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CONode_Response>);
    fn canopen_interfaces__srv__CONode_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CONode_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CONode_Response>) -> bool;
}

// Corresponds to canopen_interfaces__srv__CONode_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CONode_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}



impl Default for CONode_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__srv__CONode_Response__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__srv__CONode_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CONode_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__srv__CONode_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CONode_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CONode_Response where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/srv/CONode_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__srv__CONode_Response() }
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


