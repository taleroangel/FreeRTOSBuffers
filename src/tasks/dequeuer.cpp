#include "dequeuer.hxx"

#include "display.hxx"
#include "tasks.hxx"

#include <pinout.h>
#include <tasks/uart.hxx>

#include <FreeRTOS.h>
#include <semphr.h>

#include <fsl_gpio.h>
#include <fsl_uart.h>

namespace tasks::dequeuer {
/* --------- Variable definition --------- */
TaskHandle_t handler = nullptr;

/* --------- Function definition --------- */
void data_dequeuer_task(void *) {

  // Take wake time
  TickType_t last_wake_up = xTaskGetTickCount();

  // Value buffer
  tasks::queue_item_t item_buff = 0U;

  // Queue size buffer
  float queue_size;
  UBaseType_t queue_items_size;

  while (true) {

    // Grab value from Queue and store it in item_buff
    if (xQueueReceive(tasks::data_queue, (void *)&item_buff, portMAX_DELAY) ==
        pdTRUE) {
      // Grab the lock on display
      if (xSemaphoreTake(tasks::display::mux_data, portMAX_DELAY) == pdPASS) {
        // Store the value in display data
        tasks::display::display_data = item_buff;
        // Release the lock
        xSemaphoreGive(tasks::display::mux_data);
      }
    }

    // Apply delay to task
    vTaskDelayUntil(&last_wake_up, DEQUEUER_TASK_TICKS);

    // Calculate queue size
    queue_items_size = uxQueueMessagesWaiting(tasks::data_queue);
    queue_size = ((float)queue_items_size / (float)tasks::queue_size);

    // Enable the UART
    if ((queue_size < (1.0F - tasks::queue_max)) &&
        (tasks::uart::uart_is_activated == false)) {
      xSemaphoreTake(tasks::uart::uart_semaphore, portMAX_DELAY);
      // Activate UART
      if ((kUART_TxDataRegEmptyFlag)&UART_GetStatusFlags(CONFIG_UART)) {
        UART_WriteByte(CONFIG_UART, UART_XON);
      }
      GPIO_PinWrite(BUILTIN_LED_G_GPIO, BUILTIN_LED_G_PIN, BUILTIN_LED_ON);
      // Set activation variable
      tasks::uart::uart_is_activated = true;
      xSemaphoreGive(tasks::uart::uart_semaphore);
    }
  }
}
} // namespace tasks::dequeuer