#include "data.h"

SemaphoreHandle_t uart_semaphore = NULL;
QueueHandle_t intermediate_queue = NULL;

SemaphoreHandle_t uart_is_activated_mutex;
uint8_t uart_is_activated = 1;

void init_data(void) {
  uart_is_activated_mutex = xSemaphoreCreateMutex();
  uart_semaphore = xSemaphoreCreateCounting(SEMAPHORE_COUNT, 0);
  intermediate_queue = xQueueCreate(QUEUE_SIZE, sizeof(queue_item_t));
}