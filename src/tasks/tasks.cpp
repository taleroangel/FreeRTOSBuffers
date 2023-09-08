#include "tasks.hxx"

namespace tasks {
QueueHandle_t data_queue = nullptr;

/**
 * @brief Initialize data queue between dequeuer and display
 * @return int pdFAIL on Failure or pdPASS on Success
 */
int init_variables() {
  // Initialize the queue
  tasks::data_queue =
      xQueueCreate(tasks::queue_size, sizeof(tasks::queue_item_t));

  if (tasks::data_queue == nullptr)
    return pdFAIL;

  // Return success
  return pdTRUE;
}

} // namespace tasks