#ifndef __DATA_H__
#define __DATA_H__

#include <FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#include <stdint.h>

#define SEMAPHORE_COUNT 35
#define QUEUE_SIZE 35

/// @brief Item to be put in the queue
typedef uint8_t queue_item_t;

/**
 * @brief Inicializar los semaforos
 */
void init_data(void);

/// @brief Semáforo de la UART
extern SemaphoreHandle_t uart_semaphore;

extern SemaphoreHandle_t uart_is_activated_mutex;
extern uint8_t uart_is_activated;

/// @brief Queue between interruption and task
extern QueueHandle_t intermediate_queue;

#endif