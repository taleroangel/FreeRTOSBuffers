/* --------- Private includes --------- */
#include <pinout.h>

#include <drivers/display.hxx>

#include <tasks/dequeuer.hxx>
#include <tasks/display.hxx>
#include <tasks/tasks.hxx>

/* --------- Includes --------- */

/* Board Configuration */
#include <board.h>
#include <clock_config.h>
#include <pin_mux.h>

/* FreeRTOS include */
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

/* FreeScale SDK */
#include <fsl_debug_console.h>
#include <fsl_gpio.h>

/* --------- Declaration --------- */

/// @brief Initialize the board pinout and electrical features
void init_board();

/// @brief Initialize the custom drivers
void init_drivers();

/// @brief Create FreeRTOS defined tasks
/// @return FreeRTOS error or pdPASS
BaseType_t init_tasks();

/* --------- Main variables --------- */
drivers::display display_driver = {};

/* --------- Entrypoint --------- */
int main(void) {

  {
    // Initialization routines
    init_board();
    init_drivers();

    BaseType_t retval = init_tasks();
    if (retval != pdPASS) {
      PRINTF("Error during task creation\r\n", retval);
      return EXIT_FAILURE;
    }
  } // Memory cleanup after block

  // Start the scheduler
  vTaskStartScheduler();

  // Execution Loop
  while (true)
    ;
}

/* --------- Definition --------- */

void init_board() {
  gpio_pin_config_t pin_config = {
      kGPIO_DigitalOutput,
      0,
  };

  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  GPIO_PinInit(BUILTIN_LED_GPIO, BUILTIN_LED_PIN, &pin_config);
}

void init_drivers() { display_driver.init(); }

BaseType_t init_tasks() {
  // Store return types
  BaseType_t task_return_status = 0U;

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

  // Return with no errors
  return task_return_status;
}
