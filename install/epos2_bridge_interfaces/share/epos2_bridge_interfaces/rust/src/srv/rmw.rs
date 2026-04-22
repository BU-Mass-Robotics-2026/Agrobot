#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta_Request() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveDelta_Request__init(msg: *mut MoveDelta_Request) -> bool;
    fn epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Request>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Request>);
    fn epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveDelta_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Request>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveDelta_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveDelta_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub delta_rad: f64,

}



impl Default for MoveDelta_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveDelta_Request__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveDelta_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveDelta_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveDelta_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveDelta_Request where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveDelta_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta_Request() }
  }
}


#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta_Response() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveDelta_Response__init(msg: *mut MoveDelta_Response) -> bool;
    fn epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Response>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Response>);
    fn epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveDelta_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveDelta_Response>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveDelta_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveDelta_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for MoveDelta_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveDelta_Response__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveDelta_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveDelta_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveDelta_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveDelta_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveDelta_Response where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveDelta_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveDelta_Response() }
  }
}


#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute_Request() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Request__init(msg: *mut MoveAbsolute_Request) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Request>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Request>);
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveAbsolute_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Request>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsolute_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsolute_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_rad: f64,

}



impl Default for MoveAbsolute_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveAbsolute_Request__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveAbsolute_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveAbsolute_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveAbsolute_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveAbsolute_Request where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveAbsolute_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute_Request() }
  }
}


#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute_Response() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Response__init(msg: *mut MoveAbsolute_Response) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Response>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Response>);
    fn epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveAbsolute_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveAbsolute_Response>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsolute_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsolute_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for MoveAbsolute_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveAbsolute_Response__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveAbsolute_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveAbsolute_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsolute_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveAbsolute_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveAbsolute_Response where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveAbsolute_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsolute_Response() }
  }
}


#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(msg: *mut MoveAbsoluteTimed_Request) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Request>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Request>);
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Request>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveAbsoluteTimed_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveAbsoluteTimed_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveAbsoluteTimed_Request where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request() }
  }
}


#[link(name = "epos2_bridge_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response() -> *const std::ffi::c_void;
}

#[link(name = "epos2_bridge_interfaces__rosidl_generator_c")]
extern "C" {
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(msg: *mut MoveAbsoluteTimed_Response) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Response>, size: usize) -> bool;
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Response>);
    fn epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<MoveAbsoluteTimed_Response>) -> bool;
}

// Corresponds to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MoveAbsoluteTimed_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for MoveAbsoluteTimed_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(&mut msg as *mut _) {
        panic!("Call to epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MoveAbsoluteTimed_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MoveAbsoluteTimed_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MoveAbsoluteTimed_Response where Self: Sized {
  const TYPE_NAME: &'static str = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response() }
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


