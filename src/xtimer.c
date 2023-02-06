/**
 * @file xtimer.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of xtimer.
 * @version 0.1.0
 * @date 2023-01-25
 * 
 */

#include "xtimer.h"
#include <assert.h>
#include <time.h>

enum _xtimer_status {
	_XTIMER_INITED,
	_XTIMER_RUNNING,
	_XTIMER_STOP,

	_XTIMER_END,
};

void xtimer_init(xtimer *tm)
{
	assert(NULL != tm);
	tm->_status = _XTIMER_INITED;
}

int xtimer_start(xtimer *tm)
{
	assert(NULL != tm);
	if (_XTIMER_INITED != tm->_status)
		return -1;
	timespec_get(&tm->_begin, TIME_UTC);
	tm->_status = _XTIMER_RUNNING;
	return 0;
}

int xtimer_stop(xtimer *tm)
{
	assert(NULL != tm);
	if (_XTIMER_RUNNING != tm->_status)
		return -1;
	timespec_get(&tm->_end, TIME_UTC);
	tm->_status = _XTIMER_STOP;
	return 0;
}

int xtimer_reset(xtimer *tm)
{
	assert(NULL != tm);
	if (_XTIMER_STOP != tm->_status)
		return -1;
	tm->_status = _XTIMER_INITED;
	return 0;
}

double xtimer_s(xtimer *tm)
{
	assert(NULL != tm);
	if (_XTIMER_STOP != tm->_status)
		return -1;
	return (tm->_end.tv_sec - tm->_begin.tv_sec)
		+ (double)(tm->_end.tv_nsec - tm->_begin.tv_nsec)
		/ 1000000000.0;
}

long xtimer_ns(xtimer *tm)
{
	assert(NULL != tm);
	if (_XTIMER_STOP != tm->_status)
		return -1;
	return (tm->_end.tv_sec - tm->_begin.tv_sec) * 1000000000
		+ (tm->_end.tv_nsec - tm->_begin.tv_nsec);
}
