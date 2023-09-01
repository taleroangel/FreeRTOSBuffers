#include "uart.hxx"

namespace tasks::uart {

/* --------- Variable initialization --------- */
TaskHandle_t handler = nullptr;

/* --------- Function declaration --------- */
void uart_controller_task(void *) {
  while (true) {
    vTaskDelay(1000U);
  }
}
} // namespace tasks::uart