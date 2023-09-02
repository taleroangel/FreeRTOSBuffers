#include "uart.hxx"
#include <pinout.h>
#include <tasks/tasks.hxx>
extern "C" {
#include <data/data.h>
}

#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#include <fsl_gpio.h>
#include <fsl_uart.h>

namespace tasks::uart {

/* --------- Variable initialization --------- */
TaskHandle_t handler = nullptr;

/* --------- Function declaration --------- */
void uart_controller_task(void *) {

  float queue_size;
  UBaseType_t queue_items_size;
  queue_item_t data;

  while (true) {
    // Pedir el semáforo
    if ((xSemaphoreTake(uart_semaphore, portMAX_DELAY) == pdTRUE) &&
        (xQueueReceive(intermediate_queue, &data, portMAX_DELAY) == pdTRUE)) {

      // Enviar los datos al display
      xQueueSend(tasks::data_queue, (tasks::queue_item_t *)&data,
                 portMAX_DELAY);

      // Calcular el tamaño de la cola (llenos)
      queue_items_size = uxQueueMessagesWaiting(tasks::data_queue);
      queue_size = ((float)queue_items_size / (float)tasks::queue_size);

      // Enviar el XOFF
      if ((queue_size > tasks::queue_max) && (uart_is_activated == 1)) {
		xSemaphoreTake(uart_is_activated_mutex, portMAX_DELAY);
        // Solicitar activar la UART
        uint8_t uart_status = UART_XOFF;
        UART_WriteBlocking(UART_BASE, &uart_status, sizeof(uart_status));
        GPIO_PinWrite(BUILTIN_LED_GPIO, BUILTIN_LED_PIN, BUILTIN_LED_OFF);
		uart_is_activated = 0;
		xSemaphoreGive(uart_is_activated_mutex);
      }
    }
  }
}
} // namespace tasks::uart