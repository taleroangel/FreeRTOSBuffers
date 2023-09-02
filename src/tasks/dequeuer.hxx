#ifndef __DEQUEUER_TASK_HXX__
#define __DEQUEUER_TASK_HXX__

#include <FreeRTOS.h>
#include <task.h>

/// Sample at which the data will be pulled out of the queue
#define DEQUEUER_TASK_SAMPLE_HZ (80U)
#define DEQUEUER_TASK_TICKS                                                    \
  (unsigned int)(configTICK_RATE_HZ / DEQUEUER_TASK_SAMPLE_HZ)

namespace tasks::dequeuer {

/// @brief Task name
constexpr char k_name[] = "DataDequeuer";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 10U;

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Update the display every DISPLAY_TICKS
 * @param pvParams display_driver as parameter
 */
void data_dequeuer_task(void *);
} // namespace tasks::dequeuer

#endif
