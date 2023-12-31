#include "display.hxx"

#include <drivers/display.hxx>

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

#include <cstdio>
#include <cstring>

namespace tasks::display {

/* --------- Variable initialization --------- */
SemaphoreHandle_t mux_data = nullptr;
uint8_t display_data = 0U;
TaskHandle_t handler = nullptr;

/* --------- Function declaration --------- */
int init_variables() {
  // Initialize the mutex
  mux_data = xSemaphoreCreateMutex();
  if (mux_data == nullptr)
    return pdFAIL;

  // Return success
  return pdPASS;
}

void update_display_task(void *pv_display_driver) {

  // Parameter guard
  if (pv_display_driver == nullptr) // No parameter was sent
    vTaskDelete(nullptr);           // Destroy itself

  // Unwrap the display_driver from parameters
  drivers::display *display_driver = (drivers::display *)pv_display_driver;

  // Take wake time
  TickType_t last_wake_time = xTaskGetTickCount();

  while (true) {
    // Take muxtex and grab the value
    if (xSemaphoreTake(mux_data, DISPLAY_TASK_MAX_WAIT) == pdPASS) {
      // Get the number and set the character
      char characters[DISPLAY_NUMBER_OF_SECTIONS + 1] = "\0";
      std::sprintf(characters, "%d", display_data);

      // Update display
      display_driver->set(characters, std::strlen(characters));

      // Release mutex
      if (xSemaphoreGive(mux_data) == pdFALSE)
        vTaskDelete(nullptr);
    }

    // Update the display
    display_driver->update();

    // Apply delay
    vTaskDelayUntil(&last_wake_time, DISPLAY_TASK_TICKS);
  }

  // Delete task if some break condition is set
  vTaskDelete(nullptr);
}
} // namespace tasks::display