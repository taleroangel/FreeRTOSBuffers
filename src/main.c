/* --------- Project configuration --------- */
#include <pinout.h>
#include <tasks/init.h>

/* --------- FreeRTOS --------- */
#include <FreeRTOS.h>
#include <task.h>

/* Board Configuration */
#include <MKL46Z4.h>
#include <board.h>
#include <clock_config.h>
#include <pin_mux.h>

/* FreeScale SDK */
#include <fsl_debug_console.h>
#include <fsl_gpio.h>

/**
 * @brief Initialize board configuration and GPIO
 */
void init_board(void);

/* --------- Application entry point --------- */
int main(void) {

  // 1. Initialize board pins
  init_board();

  // 2. Initialize the display driver
  init_display();

  // 3. Initialize semaphores and mutex
  if (init_variables() != pdPASS)
    return EXIT_FAILURE;

  // 4. Initialize UART
  init_uart();

  // 5. Initialize tasks
  if (init_freertos() != pdPASS) {
    return EXIT_FAILURE;
  }

  // Init scheduler
  vTaskStartScheduler();

  // Infinite Loop
  for (;;)
    ;
}

/* --------- Function definitions --------- */
void init_board(void) {
  // Create GPIO configuration
  gpio_pin_config_t pin_config = {
      kGPIO_DigitalOutput,
      BUILTIN_LED_ON,
  };

  // Initialize board properties
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  // Initialize the LED
  pin_config.outputLogic = BUILTIN_LED_OFF;
  GPIO_PinInit(BUILTIN_LED_R_GPIO, BUILTIN_LED_R_PIN, &pin_config);

  pin_config.outputLogic = BUILTIN_LED_ON;
  GPIO_PinInit(BUILTIN_LED_G_GPIO, BUILTIN_LED_G_PIN, &pin_config);
}