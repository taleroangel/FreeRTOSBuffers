#include "dequeuer.hxx"

#include "display.hxx"

#include <FreeRTOS.h>
#include <semphr.h>

namespace tasks::dequeuer {
/* --------- Variable definition --------- */
TaskHandle_t handler = nullptr;

/* --------- Function definition --------- */
void data_dequeuer_task(void *) {

  // Take wake time
  TickType_t last_wake_up = xTaskGetTickCount();

  while (true) {
	// Grab the lock on display
	if (xSemaphoreTake(tasks::display::mux_data, portMAX_DELAY) == pdPASS) {
		
		// TODO: Actually grab values from the queue
		{
			static uint8_t counter = 0U;
			tasks::display::data = counter;
			counter++;
		}
		
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