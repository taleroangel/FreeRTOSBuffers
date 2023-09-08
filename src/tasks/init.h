#ifndef __CPP_BINDINGS_H__
#define __CPP_BINDINGS_H__

/* --------- C++ Extern Binding --------- */
#ifdef __cplusplus
extern "C" {
#endif

//! Must follow initialization order

/**
 * @brief Initialization routines for the Display
 */
void init_display(void);

/**
 * @brief Initialize semaphores and mutex
 *
 */
int init_variables(void);

/**
 * @brief Initialize the UART
 */
void init_uart(void);

/**
 * @brief Initialization routines for FreeRTOS tasks
 */
int init_freertos(void);

#ifdef __cplusplus
}
#endif

#endif