# Append FreeRTOS definitions
defines += ['-DFSL_RTOS_FREE_RTOS']

project_inc += [
    include_directories('.'),
    include_directories('lib/FreeRTOS/portable/GCC/ARM_CM0'),
    include_directories('lib/include/private'),
    include_directories('lib/include'),
]

freertos_src = [
    files('lib/FreeRTOS/event_groups.c'),
    files('lib/FreeRTOS/list.c'),
    files('lib/FreeRTOS/queue.c'),
    files('lib/FreeRTOS/stream_buffer.c'),
    files('lib/FreeRTOS/tasks.c'),
    files('lib/FreeRTOS/timers.c'),
    files('lib/FreeRTOS/portable/GCC/ARM_CM0/fsl_tickless_systick.c'),
    files('lib/FreeRTOS/portable/GCC/ARM_CM0/port.c'),
    files('lib/FreeRTOS/portable/MemMang/heap_1.c'),
    files('lib/FreeRTOS/portable/MemMang/heap_2.c'),
    files('lib/FreeRTOS/portable/MemMang/heap_3.c'),
    files('lib/FreeRTOS/portable/MemMang/heap_4.c'),
    files('lib/FreeRTOS/portable/MemMang/heap_5.c'),
]
