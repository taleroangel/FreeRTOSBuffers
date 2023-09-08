#ifndef __TASKS_HXX__
#define __TASKS_HXX__

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <queue.h>

#define TASKS_QUEUE_SIZE 64
#define TASKS_QUEUE_MAX 0.75

namespace tasks {

/// @brief Element type allocated in queue
using queue_item_t = uint8_t;

/// @brief Ammount of allowed elements in queue
constexpr unsigned int queue_size = TASKS_QUEUE_SIZE;
constexpr float queue_max = TASKS_QUEUE_MAX;

/// @brief Queue in which to put the incoming Serial data
extern QueueHandle_t data_queue;

int init_variables();

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