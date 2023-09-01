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
void initialize_display() { display_driver.init(); }

int initialize_freertos() {
  // Store return types
  BaseType_t task_return_status = 0U;

  // Initialize the queue
  tasks::data_queue =
      xQueueCreate(tasks::queue_size, sizeof(tasks::queue_item_t));
  if (tasks::data_queue == nullptr)
    return pdFAIL;

  // Initialize the mutex
  tasks::display::mux_data = xSemaphoreCreateMutex();
  if (tasks::display::mux_data == nullptr)
    return pdFAIL;

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
           tasks::HIGH_PRIORITY, &tasks::dequeuer::handler)) != pdPASS) {
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
