#ifndef __DISPLAY_TASK_HXX__
#define __DISPLAY_TASK_HXX__

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#define DISPLAY_TASK_TICKS                                                     \
  (unsigned int)(configTICK_RATE_HZ / DISPLAY_REFRESH_RATE)

namespace tasks::display {
/* --------- Global Variables --------- */
// ! Access to this variables must be done in the order they are declared here!

extern SemaphoreHandle_t mux_data;
extern uint8_t data;

/* --------- Constants --------- */

/// @brief Task name
constexpr char k_name[] = "DisplayUpdate";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 10U;

/* --------- Tasks --------- */

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Update the display every DISPLAY_TICKS
 * @param pvParams display_driver as parameter
 */
void update_display_task(void *param);
} // namespace tasks::display

#endif