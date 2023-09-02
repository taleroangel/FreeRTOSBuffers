#include "interrupt.h"

#include <data/data.h>
#include <pinout.h>

#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#include <board.h>
#include <clock_config.h>
#include <pin_mux.h>

#include <fsl_uart.h>

#define CONFIG_UART UART_BASE
#define CONFIG_UART_CLKSRC BUS_CLK
#define CONFIG_UART_CLK_FREQ CLOCK_GetFreq(BUS_CLK)
#define CONFIG_UART_IRQn UART1_IRQn
#define CONFIG_UART_IRQHandler UART1_IRQHandler

/**
 * @brief Manejador de interrupciones
 *
 */
void CONFIG_UART_IRQHandler(void) {
  BaseType_t _ = pdFALSE;
  queue_item_t data;

  // Grab the data
  if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) &
      UART_GetStatusFlags(CONFIG_UART)) {
    // Grab value from ISR
    data = UART_ReadByte(CONFIG_UART);
    // Send data to QUEUE
    xQueueSendFromISR(intermediate_queue, (void *)&data, &_);
    xSemaphoreGiveFromISR(uart_semaphore, &_);
  }

  // YIELD
  portYIELD_FROM_ISR(_);
}

/**
 * @brief Inicializar las interrupciones del UART
 *
 */
void init_uart(void) {

  /* Setup UART configuration */
  uart_config_t config;
  UART_GetDefaultConfig(&config);
  config.baudRate_Bps = UART_BAUD_RATE;
  config.enableTx = true;
  config.enableRx = true;

  /* Initialize the UART */
  UART_Init(CONFIG_UART, &config, CONFIG_UART_CLK_FREQ);

  /* Enable RX interrupt. */
  UART_EnableInterrupts(CONFIG_UART, kUART_RxDataRegFullInterruptEnable |
                                         kUART_RxOverrunInterruptEnable);
  EnableIRQ(CONFIG_UART_IRQn);
}
