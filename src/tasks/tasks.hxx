#ifndef __TASKS_HXX__
#define __TASKS_HXX__

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <queue.h>

#define TASKS_QUEUE_SIZE 64

namespace tasks {

/// @brief Element type allocated in queue
using queue_item_t = uint8_t;

/// @brief Ammount of allowed elements in queue
constexpr unsigned int queue_size = TASKS_QUEUE_SIZE;

/// @brief Queue in which to put the incoming Serial data
extern QueueHandle_t data_queue;

/// @brief Tasks standarized priorities
enum : UBaseType_t {
  LOWEST_PRIORITY = 0UL,
  LOW_PRIORITY = 1UL,
  STANDARD_PRIORITY = 2UL,
  HIGH_PRIORITY = 3UL,
  CRITICAL_PRIORITY = (configMAX_PRIORITIES - 1UL)
};
} // namespace tasks

#endif