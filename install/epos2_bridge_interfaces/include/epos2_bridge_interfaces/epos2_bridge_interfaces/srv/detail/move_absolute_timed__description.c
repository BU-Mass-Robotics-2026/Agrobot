// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from epos2_bridge_interfaces:srv/MoveAbsoluteTimed.idl
// generated code does not contain a copyright notice

#include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_type_hash_t *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc0, 0xf2, 0xf4, 0x23, 0x94, 0xef, 0x98, 0xf1,
      0x88, 0x00, 0x6f, 0x48, 0xa4, 0x09, 0xf9, 0x7e,
      0xe2, 0xdd, 0x87, 0x1f, 0xdd, 0x1a, 0xbd, 0x3c,
      0x55, 0x43, 0x59, 0x70, 0xb6, 0x7b, 0xdc, 0xde,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_type_hash_t *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf4, 0x59, 0x1b, 0x9c, 0x0b, 0x9e, 0x9b, 0x65,
      0xa8, 0xf1, 0x2b, 0xe4, 0x73, 0xd0, 0xcd, 0x0e,
      0x7a, 0xea, 0x21, 0x1a, 0xe0, 0xc5, 0x72, 0x92,
      0x08, 0x4c, 0xfb, 0x2c, 0x8f, 0xdd, 0x38, 0x45,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_type_hash_t *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x73, 0x74, 0xbc, 0x9d, 0x4e, 0xcd, 0x88, 0x3c,
      0x57, 0x17, 0xf1, 0x35, 0x4f, 0x13, 0x6a, 0xcc,
      0x2b, 0xf1, 0x4b, 0x62, 0x42, 0x64, 0x24, 0x6d,
      0xd7, 0x10, 0xbe, 0x76, 0x83, 0xae, 0xe4, 0x56,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_epos2_bridge_interfaces
const rosidl_type_hash_t *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8c, 0x9f, 0xc5, 0xd8, 0xa3, 0x6c, 0x43, 0x3e,
      0x25, 0x23, 0xf5, 0x4e, 0x7c, 0xf3, 0x58, 0x61,
      0x7a, 0xda, 0xe5, 0x03, 0xd6, 0x15, 0xc6, 0xb7,
      0xa6, 0x4b, 0x4b, 0xf4, 0x52, 0xab, 0x89, 0xd3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed__TYPE_NAME[] = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__TYPE_NAME[] = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed_Event";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME[] = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed_Request";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME[] = "epos2_bridge_interfaces/srv/MoveAbsoluteTimed_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__request_message[] = "request_message";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__response_message[] = "response_message";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELDS[] = {
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__TYPE_NAME, 51, 51},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription epos2_bridge_interfaces__srv__MoveAbsoluteTimed__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__TYPE_NAME, 51, 51},
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__TYPE_NAME, 45, 45},
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__FIELDS, 3, 3},
    },
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELD_NAME__target_rad[] = "target_rad";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELD_NAME__duration_sec[] = "duration_sec";

static rosidl_runtime_c__type_description__Field epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELDS[] = {
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELD_NAME__target_rad, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELD_NAME__duration_sec, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELD_NAME__success[] = "success";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELDS[] = {
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__info[] = "info";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__request[] = "request";
static char epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELDS[] = {
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
    },
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
    {NULL, 0, 0},
  },
  {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__TYPE_NAME, 51, 51},
      {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__FIELDS, 3, 3},
    },
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 target_rad\n"
  "float64 duration_sec\n"
  "---\n"
  "bool success\n"
  "string message";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed__TYPE_NAME, 45, 45},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 72, 72},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__TYPE_NAME, 53, 53},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__TYPE_NAME, 54, 54},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__TYPE_NAME, 51, 51},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_individual_type_description_source(NULL);
    sources[3] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_individual_type_description_source(NULL);
    sources[4] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__get_individual_type_description_source(NULL);
    sources[3] = *epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
