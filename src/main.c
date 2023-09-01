/* --------- Project configuration --------- */
#include <pinout.h>
#include <tasks/init.h>
#include <tasks/interrupt.h>

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
  // 1. Initialize the board
  init_board();
  // 2. Initialize the UART
  init_uart();
  // 3. 
  initialize_display();

  // Infinite Loop
  for (;;)
    ;
}

/* --------- Function definitions --------- */
void init_board(void) {
  // Create GPIO configuration
  gpio_pin_config_t pin_config = {
      kGPIO_DigitalOutput,
      0,
  };

  // Initialize board properties
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  // Initialize the LED
  GPIO_PinInit(BUILTIN_LED_GPIO, BUILTIN_LED_PIN, &pin_config);
}