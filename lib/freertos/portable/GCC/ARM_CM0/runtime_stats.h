#ifndef __RUNTIME_STATS_H__
#define __RUNTIME_STATS_H__

#include <stdint.h>

extern volatile uint32_t runtime_stats_timer_ticks;

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() (runtime_stats_timer_ticks = 0UL)
#define portGET_RUN_TIME_COUNTER_VALUE() (runtime_stats_timer_ticks++)

#endif