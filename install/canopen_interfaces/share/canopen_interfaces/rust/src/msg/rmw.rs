#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "canopen_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__msg__COData() -> *const std::ffi::c_void;
}

#[link(name = "canopen_interfaces__rosidl_generator_c")]
extern "C" {
    fn canopen_interfaces__msg__COData__init(msg: *mut COData) -> bool;
    fn canopen_interfaces__msg__COData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<COData>, size: usize) -> bool;
    fn canopen_interfaces__msg__COData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<COData>);
    fn canopen_interfaces__msg__COData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<COData>, out_seq: *mut rosidl_runtime_rs::Sequence<COData>) -> bool;
}

// Corresponds to canopen_interfaces__msg__COData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct COData {

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



impl Default for COData {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !canopen_interfaces__msg__COData__init(&mut msg as *mut _) {
        panic!("Call to canopen_interfaces__msg__COData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for COData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__msg__COData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__msg__COData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { canopen_interfaces__msg__COData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for COData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for COData where Self: Sized {
  const TYPE_NAME: &'static str = "canopen_interfaces/msg/COData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__canopen_interfaces__msg__COData() }
  }
}


