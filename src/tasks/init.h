#ifndef __CPP_BINDINGS_H__
#define __CPP_BINDINGS_H__

/* --------- C++ Extern Binding --------- */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialization routines for the Display
 */
void initialize_display(void);

/**
 * @brief Initialization routines for FreeRTOS tasks
 */
int initialize_freertos(void);

#ifdef __cplusplus
}
#endif

#endif