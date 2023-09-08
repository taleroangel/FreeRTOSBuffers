extern "C" {
#include "init.h"
}

/* --------- Private includes --------- */
#include <drivers/display.hxx>
#include <pinout.h>

#include <tasks/dequeuer.hxx>
#include <tasks/display.hxx>
#include <tasks/tasks.hxx>
#include <tasks/uart.hxx>

/* --------- Includes --------- */

/* FreeRTOS include */
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

/* --------- Global Variables --------- */
drivers::display display_driver = {};

/* --------- Definition --------- */
void init_display() { display_driver.init(); }

int init_freertos() {
  // Store return types
  BaseType_t task_return_status = 0U;

  // Create display update task
  if ((task_return_status = xTaskCreate(
           tasks::display::update_display_task, tasks::display::k_name,
           (configMINIMAL_STACK_SIZE + tasks::display::k_stack),
           (void *)&display_driver, tasks::STANDARD_PRIORITY,
           &tasks::display::handler)) != pdPASS) {
    // Cleanup and Return error
    vTaskDelete(tasks::display::handler);
    return task_return_status;
  }

  // Create the dequeuer task
  if ((task_return_status = xTaskCreate(
           tasks::dequeuer::data_dequeuer_task, tasks::dequeuer::k_name,
           (configMINIMAL_STACK_SIZE + tasks::dequeuer::k_stack), nullptr,
           tasks::CRITICAL_PRIORITY, &tasks::dequeuer::handler)) != pdPASS) {
    vTaskDelete(tasks::dequeuer::handler);
    return task_return_status;
  }

  // Initialize the UART task
  if ((task_return_status = xTaskCreate(
           tasks::uart::uart_controller_task, tasks::uart::k_name,
           (configMINIMAL_STACK_SIZE + tasks::uart::k_stack), nullptr,
           tasks::CRITICAL_PRIORITY, &tasks::uart::handler)) != pdPASS) {
    vTaskDelete(tasks::uart::handler);
    return task_return_status;
  }

  // Return with no errors
  return task_return_status;
}

void init_uart() {

  /* Setup UART configuration */
  uart_config_t config;
  UART_GetDefaultConfig(&config);

  config.baudRate_Bps = UART_BAUD_RATE;
  config.parityMode = kUART_ParityDisabled;
  config.stopBitCount = kUART_OneStopBit;
  config.enableTx = true;
  config.enableRx = true;

  /* Initialize the UART */
  UART_Init(CONFIG_UART, &config, CONFIG_UART_CLK_FREQ);

  /* Enable RX interrupt. */
  UART_EnableInterrupts(CONFIG_UART, kUART_RxDataRegFullInterruptEnable |
                                         kUART_RxOverrunInterruptEnable);
  EnableIRQ(CONFIG_UART_IRQn);
}

int init_variables() {
  int retval = 0;

  // Initialize generic tasks
  if ((retval = tasks::init_variables()) != pdPASS)
    return pdFAIL;

  // Initialize display tasks
  if ((retval = tasks::display::init_variables()) != pdPASS)
    return pdFAIL;

  // Initialize uart tasks
  if ((retval = tasks::uart::init_variables()) != pdPASS)
    return pdFAIL;

  return pdPASS;
}