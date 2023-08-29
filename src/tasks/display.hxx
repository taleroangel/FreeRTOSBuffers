#ifndef __DISPLAY_TASK_HXX__
#define __DISPLAY_TASK_HXX__

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <drivers/display.hxx>

/// How many ticks does the display have to wait for a refresh
#define DISPLAY_TASK_TICKS                                                     \
  (unsigned int)(configTICK_RATE_HZ / DISPLAY_REFRESH_RATE)

/// Maximum wait time for lock to avoid frame drop
#define DISPLAY_TASK_MAX_WAIT (2 * DISPLAY_TASK_TICKS)

namespace tasks::display {
/* --------- Global Variables --------- */

/// @brief Mutex to access this variables
/// @note Access to global data must be accessed in the same order they are
/// declared
extern SemaphoreHandle_t mux_data;

/// @brief Data to be put in the display
extern uint8_t display_data;

/* --------- Constants --------- */

/// @brief Task name
constexpr char k_name[] = "DisplayUpdate";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 60U;

/* --------- Tasks --------- */

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Update the display every DISPLAY_TICKS
 * @param pv_display_driver display_driver as parameter
 */
void update_display_task(void *pv_display_driver);
} // namespace tasks::display

#endif