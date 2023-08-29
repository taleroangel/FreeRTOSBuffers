#include "uart.hxx"

#include <pinout.h>

#include <fsl_uart.h>
#include <fsl_uart_freertos.h>

namespace tasks::uart {
/* --------- Variable definition
--------- */
uint8_t uart_data = 0U;
TaskHandle_t handler = nullptr;

/* --------- Task definition --------- */
void uart_controller_task(void *) {
  // Setup the UART
  uart_rtos_handle_t uart_rtos_handler;
  uart_handle_t uart_handler;
  uint8_t background_buffer[32];
  uart_rtos_config_t uart_config = {
      .base = (UART_Type *)UART_BASE,
      .srcclk = CLOCK_GetFreq(BUS_CLK),
      .baudrate = k_baud_rate,
      .parity = kUART_ParityDisabled,
      .stopbits = kUART_OneStopBit,
      .buffer = background_buffer,
      .buffer_size = sizeof(background_buffer),
  };

  // Initialize the UART
  if (UART_RTOS_Init(&uart_rtos_handler, &uart_handler, &uart_config) != 0) {
    vTaskDelete(nullptr);
  }

  // Send data to UART
  uint8_t data[] = {'H', 'O', 'L', 'A', '\r', '\n'};

  // Do nothing
  while (true) {
    UART_RTOS_Send(&uart_rtos_handler, data, sizeof(data));
    vTaskDelay(100U);
  }
}

} // namespace tasks::uart
