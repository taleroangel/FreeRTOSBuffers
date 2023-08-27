#ifndef __TASKS_HXX__
#define __TASKS_HXX__

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>

namespace tasks {
enum : UBaseType_t {
  LOWEST_PRIORITY = 0UL,
  LOW_PRIORITY = 1UL,
  STANDARD_PRIORITY = 2UL,
  HIGH_PRIORITY = 3UL,
  CRITICAL_PRIORITY = (configMAX_PRIORITIES - 1UL)
};
}

#endif