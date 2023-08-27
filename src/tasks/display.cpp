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
uint8_t data = 0U;
TaskHandle_t handler = nullptr;

/* --------- Function declaration --------- */
void update_display_task(void *param) {

  // Parameter guard
  if (param == nullptr)   // No parameter was sent
    vTaskDelete(nullptr); // Destroy itself

  // Unwrap the display_driver from parameters
  drivers::display *display_driver = (drivers::display *)param;

  // Take wake time
  TickType_t last_wake_time = xTaskGetTickCount();

  while (true) {
    // Take muxtex and grab the value
    if (xSemaphoreTake(mux_data, portMAX_DELAY) == pdPASS) {

      char characters[DISPLAY_NUMBER_OF_SECTIONS + 1] = "\0";
      std::sprintf(characters, "%d", data);

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