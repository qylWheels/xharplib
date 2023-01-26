/**
 * @file ice_timer.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of ice_timer.
 * @version 0.1.0
 * @date 2023-01-25
 * 
 */

#include "ice_timer.h"
#include <assert.h>
#include <time.h>

enum _ice_timer_status {
	_ICE_TIMER_INITED,
	_ICE_TIMER_RUNNING,
	_ICE_TIMER_STOP,

	_ICE_TIMER_END,
};

void ice_timer_init(ice_timer *tm)
{
	assert(NULL != tm);
	tm->_status = _ICE_TIMER_INITED;
}

int ice_timer_start(ice_timer *tm)
{
	assert(NULL != tm);
	if (_ICE_TIMER_INITED != tm->_status)
		return -1;
	timespec_get(&tm->_begin, TIME_UTC);
	tm->_status = _ICE_TIMER_RUNNING;
	return 0;
}

int ice_timer_stop(ice_timer *tm)
{
	assert(NULL != tm);
	if (_ICE_TIMER_RUNNING != tm->_status)
		return -1;
	timespec_get(&tm->_end, TIME_UTC);
	tm->_status = _ICE_TIMER_STOP;
	return 0;
}

int ice_timer_reset(ice_timer *tm)
{
	assert(NULL != tm);
	if (_ICE_TIMER_STOP != tm->_status)
		return -1;
	tm->_status = _ICE_TIMER_INITED;
	return 0;
}

double ice_timer_s(ice_timer *tm)
{
	assert(NULL != tm);
	if (_ICE_TIMER_STOP != tm->_status)
		return -1;
	return (tm->_end.tv_sec - tm->_begin.tv_sec)
		+ (double)(tm->_end.tv_nsec - tm->_begin.tv_nsec)
		/ 1000000000.0;
}

long ice_timer_ns(ice_timer *tm)
{
	assert(NULL != tm);
	if (_ICE_TIMER_STOP != tm->_status)
		return -1;
	return (tm->_end.tv_sec - tm->_begin.tv_sec) * 1000000000
		+ (tm->_end.tv_nsec - tm->_begin.tv_nsec);
}
