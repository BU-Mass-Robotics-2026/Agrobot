// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from epos2_bridge_interfaces:srv/MoveAbsoluteTimed.idl
// generated code does not contain a copyright notice
#include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * msg)
{
  if (!msg) {
    return false;
  }
  // target_rad
  // duration_sec
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * msg)
{
  if (!msg) {
    return;
  }
  // target_rad
  // duration_sec
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // target_rad
  if (lhs->target_rad != rhs->target_rad) {
    return false;
  }
  // duration_sec
  if (lhs->duration_sec != rhs->duration_sec) {
    return false;
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // target_rad
  output->target_rad = input->target_rad;
  // duration_sec
  output->duration_sec = input->duration_sec;
  return true;
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * msg = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request));
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * data = NULL;

  if (size) {
    data = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request *)allocator.zero_allocate(size, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * array = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request * data =
      (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(msg);
    return false;
  }
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * msg = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response));
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * data = NULL;

  if (size) {
    data = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response *)allocator.zero_allocate(size, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * array = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response * data =
      (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "epos2_bridge_interfaces/srv/detail/move_absolute_timed__functions.h"

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(msg);
    return false;
  }
  // request
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__init(&msg->request, 0)) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(msg);
    return false;
  }
  // response
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__init(&msg->response, 0)) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(msg);
    return false;
  }
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__fini(&msg->request);
  // response
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__fini(&msg->response);
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * msg = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event));
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__init(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * data = NULL;

  if (size) {
    data = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event *)allocator.zero_allocate(size, sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__fini(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence *
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * array = (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence *)allocator.allocate(sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__destroy(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__are_equal(const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * lhs, const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence__copy(
  const epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * input,
  epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event * data =
      (epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!epos2_bridge_interfaces__srv__MoveAbsoluteTimed_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
