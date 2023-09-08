#ifndef __UART_TASK_HXX__
#define __UART_TASK_HXX__

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include <fsl_uart.h>

#include <cstdint>

#define CONFIG_UART UART_BASE
#define CONFIG_UART_CLKSRC BUS_CLK
#define CONFIG_UART_CLK_FREQ CLOCK_GetFreq(BUS_CLK)
#define CONFIG_UART_IRQn UART1_IRQn
#define CONFIG_UART_IRQHandler UART1_IRQHandler

#define QUEUE_SIZE 10

namespace tasks::uart {

/// @brief Task name
constexpr char k_name[] = "UartControllerTask";

/// @brief Additional memory to add to stack
constexpr unsigned int k_stack = 100U;

/* --------- Queues --------- */
using queue_item_t = uint8_t;
extern QueueHandle_t intermediate_queue;
extern SemaphoreHandle_t uart_semaphore;

/* --------- Variables --------- */
extern SemaphoreHandle_t uart_activation_mutex;
extern bool uart_is_activated;


/* --------- Tasks --------- */

/// @brief Task handler
extern TaskHandle_t handler;

/**
 * @brief Initialize semaphores and mutexes
 * @return int pdPASS if success, pdFAIL if failure
 */
int init_variables();

/**
 * @brief Recieves and sends data from UART
 */
void uart_controller_task(void *);

} // namespace tasks::uart

#endif