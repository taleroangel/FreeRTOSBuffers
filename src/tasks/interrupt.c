#include "interrupt.h"
#include <pinout.h>

#include <board.h>
#include <clock_config.h>
#include <pin_mux.h>

#include <fsl_uart.h>

#define CONFIG_UART UART1
#define CONFIG_UART_CLKSRC BUS_CLK
#define CONFIG_UART_CLK_FREQ CLOCK_GetFreq(BUS_CLK)
#define CONFIG_UART_IRQn UART1_IRQn
#define CONFIG_UART_IRQHandler UART1_IRQHandler

/**
 * @brief Manejador de interrupciones
 *
 */
void CONFIG_UART_IRQHandler(void) {
  uint8_t data;

  /* Cuando llega un nuevo dato */
  if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) &
      UART_GetStatusFlags(CONFIG_UART)) {
    data = UART_ReadByte(CONFIG_UART);
    UART_WriteByte(CONFIG_UART, data);
  }
  
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate
    overlapping exception return operation might vector to incorrect interrupt
  */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
  __DSB();
#endif
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
