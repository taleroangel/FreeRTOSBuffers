# Append FreeRTOS definitions
defines += ['-DFSL_RTOS_FREE_RTOS']

project_inc += [
    include_directories('include'),
    include_directories('portable/GCC/ARM_CM0'),
]

freertos_src = [
    # Source files
    files('src/list.c'),
    files('src/stream_buffer.c'),
    files('src/timers.c'),
    files('src/queue.c'),
    files('src/croutine.c'),
    files('src/tasks.c'),
    files('src/event_groups.c'),

    # Heap implementations
    files('portable/MemMang/heap_1.c'),
    files('portable/MemMang/heap_4.c'),
    files('portable/MemMang/heap_3.c'),
    files('portable/MemMang/heap_5.c'),
    files('portable/MemMang/heap_2.c'),

    # Common
    files('portable/Common/mpu_wrappers.c'),

    # ARM CM0 GCC
    files('portable/GCC/ARM_CM0/port.c'),
    files('portable/GCC/ARM_CM0/fsl_tickless_systick.c'),

    # low_power_tickless
    files('portable/low_power_tickless/fsl_tickless_lptmr.c'),
]
