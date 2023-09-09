#include "uart.hxx"
#include <pinout.h>
#include <tasks/dequeuer.hxx>
#include <tasks/tasks.hxx>

#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#include <fsl_gpio.h>
#include <fsl_uart.h>

namespace tasks::uart {

/* --------- Variable initialization --------- */
TaskHandle_t handler = nullptr;
QueueHandle_t intermediate_queue = nullptr;
SemaphoreHandle_t uart_semaphore = nullptr;
SemaphoreHandle_t uart_activation_mutex = nullptr;
bool uart_is_activated = true;

/* --------- Function declaration --------- */
int init_variables() {
  intermediate_queue = xQueueCreate(QUEUE_SIZE, sizeof(queue_item_t));
  uart_semaphore = xSemaphoreCreateBinary();
  uart_activation_mutex = xSemaphoreCreateMutex();

  return pdPASS;
}

void uart_controller_task(void *) {

  tasks::uart::queue_item_t data;

  while (true) {
    if (xSemaphoreTake(uart_semaphore, portMAX_DELAY) == pdTRUE) {
      // Empty the intermediate queue
      while (xQueueReceive(intermediate_queue, &data, portMAX_DELAY) ==
             pdTRUE) {

        // Send data to display
        xQueueSend(tasks::data_queue, (tasks::queue_item_t *)&data,
                   portMAX_DELAY);

        // Check queue size
        UBaseType_t queue_items = uxQueueMessagesWaiting(tasks::data_queue);
        float queue_size = ((float)queue_items / (float)tasks::queue_size);

        // Check if queue is filled
        if ((queue_size > tasks::queue_max) &&
            (tasks::uart::uart_is_activated == true)) {
          xSemaphoreTake(tasks::uart::uart_activation_mutex, portMAX_DELAY);
          // Write XOFF
          if ((kUART_TxDataRegEmptyFlag)&UART_GetStatusFlags(CONFIG_UART)) {
            UART_WriteByte(CONFIG_UART, UART_XOFF);
          }
          // LED OFF for visual reference
          GPIO_PinWrite(BUILTIN_LED_G_GPIO, BUILTIN_LED_G_PIN, BUILTIN_LED_OFF);
          // Set UART activation variable
          tasks::uart::uart_is_activated = false;
          xSemaphoreGive(tasks::uart::uart_activation_mutex);
        }
      }
    }
  }
}

} // namespace tasks::uart

/* --------- UART Interruption --------- */
extern "C" void CONFIG_UART_IRQHandler(void) {

  BaseType_t hptw = pdFALSE;
  tasks::uart::queue_item_t data;

  if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) &
      UART_GetStatusFlags(CONFIG_UART)) {
    // Grab value from ISR
    data = UART_ReadByte(CONFIG_UART);
  }

  // Check if UART signal was not catched
  if (!tasks::uart::uart_is_activated) {
    if ((kUART_TxDataRegEmptyFlag)&UART_GetStatusFlags(CONFIG_UART)) {
      UART_WriteByte(CONFIG_UART, UART_XOFF);
    }
  }

  // Send data to QUEUE
  xQueueSendFromISR(tasks::uart::intermediate_queue, (void *)&data, &hptw);
  // Send semaphore signal
  xSemaphoreGiveFromISR(tasks::uart::uart_semaphore, &hptw);

  // YIELD
  portYIELD_FROM_ISR(hptw);
}