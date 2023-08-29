#ifndef __UART_TASK_HXX__
#define __UART_TASK_HXX__

#include <FreeRTOS.h>
#include <task.h>

#include <cstdint>

#define UART_BAUD_RATE 2400

namespace tasks::uart {

/// @brief Task name
constexpr char k_name[] = "UartControllerTask";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 100U;
constexpr unsigned int k_baud_rate = UART_BAUD_RATE;

extern uint8_t uart_data;

/* --------- Tasks --------- */

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Recieves and sends data from UART
 */
void uart_controller_task(void *);

} // namespace tasks::uart

#endif