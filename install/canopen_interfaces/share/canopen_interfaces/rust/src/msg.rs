#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to canopen_interfaces__msg__COData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::COData::default())
  }
}

impl rosidl_runtime_rs::Message for COData {
  type RmwMsg = super::msg::rmw::COData;

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


