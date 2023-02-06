/**
 * @file xtimer.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Timer.
 * @version 0.1.0
 * @date 2023-01-25
 * 
 */

#ifndef __XTIMER_H
#define __XTIMER_H 1

#include "xharp.h"
#include <time.h>

struct _xtimer {
	struct timespec _begin;
	struct timespec _end;
	int _status;
};
typedef struct _xtimer xtimer;

__XBEGIN_DECLS

extern void xtimer_init(xtimer *tm);

extern int xtimer_start(xtimer *tm);

extern int xtimer_stop(xtimer *tm);

extern int xtimer_reset(xtimer *tm);

extern double xtimer_s(xtimer *tm);

extern long xtimer_ns(xtimer *tm);

__XEND_DECLS

#endif  /* !__XTIMER_H */
