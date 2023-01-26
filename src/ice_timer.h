/**
 * @file ice_timer.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Timer.
 * @version 0.1.0
 * @date 2023-01-25
 * 
 */

#ifndef __ICE_TIMER_H
#define __ICE_TIMER_H 1

#include "ice.h"
#include <time.h>

struct _ice_timer {
	struct timespec _begin;
	struct timespec _end;
	int _status;
};
typedef struct _ice_timer ice_timer;

__ICE_BEGIN_DECLS

extern void ice_timer_init(ice_timer *tm);

extern int ice_timer_start(ice_timer *tm);

extern int ice_timer_stop(ice_timer *tm);

extern int ice_timer_reset(ice_timer *tm);

extern double ice_timer_s(ice_timer *tm);

extern long ice_timer_ns(ice_timer *tm);

__ICE_END_DECLS

#endif  /* __ICE_TIMER_H */
