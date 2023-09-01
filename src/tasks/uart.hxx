#ifndef __UART_TASK_HXX__
#define __UART_TASK_HXX__

#include <FreeRTOS.h>
#include <task.h>

#include <fsl_uart.h>

#include <cstdint>

namespace tasks::uart {

/// @brief Task name
constexpr char k_name[] = "UartControllerTask";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 100U;

/* --------- Tasks --------- */

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Recieves and sends data from UART
 */
void uart_controller_task(void *);

} // namespace tasks::uart

#endif