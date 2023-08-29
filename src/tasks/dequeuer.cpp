#include "dequeuer.hxx"

#include "display.hxx"
#include "tasks.hxx"

#include <FreeRTOS.h>
#include <semphr.h>

namespace tasks::dequeuer {
/* --------- Variable definition --------- */
TaskHandle_t handler = nullptr;

/* --------- Function definition --------- */
void data_dequeuer_task(void *) {

  // Take wake time
  TickType_t last_wake_up = xTaskGetTickCount();

  // Value buffer
  tasks::queue_item_t item_buff = 0U;

  while (true) {
    if ( // Grab value from Queue and store it in item_buff
        (xQueueReceive(tasks::data_queue, (void *)&item_buff, portMAX_DELAY) ==
         pdTRUE) &&
        // Grab the lock on display
        (xSemaphoreTake(tasks::display::mux_data, portMAX_DELAY) == pdPASS)) {

      // Store the value in display data
      tasks::display::display_data = item_buff;

      // Release the lock
      xSemaphoreGive(tasks::display::mux_data);
    }

    // Apply delay to task
    vTaskDelayUntil(&last_wake_up, DEQUEUER_TASK_TICKS);
  }

  // Delete task if some break condition is set
  vTaskDelete(nullptr);
}
} // namespace tasks::dequeuer