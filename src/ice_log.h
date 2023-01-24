/**
 * @file ice_log.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Log status during runtime.
 * @version 0.1.0
 * @date 2023-01-24
 * 
 */

#ifndef __ICE_LOG_H
#define __ICE_LOG_H 1

#include "ice.h"
#include <stdio.h>

struct _ice_log_env {
	const char *_path;
};
typedef struct _ice_log_env ice_log_env;

__ICE_BEGIN_DECLS

extern void ice_log_setenv(ice_log_env *env, const char *path);

extern int (ice_log_log)(ice_log_env *env, const char *fmt,
		const char *func, const char *file, int line, ...);

__ICE_END_DECLS

#ifdef ICE_NOLOG
# define ice_log_log(penv, fmt, ...) ((void)0)
#else  /* ICE_NOLOG */
# define ice_log_log(penv, fmt, ...)	\
	ice_log_log(penv, fmt, __FUNCTION__, __FILE__,	\
			__LINE__, ##__VA_ARGS__)
#endif  /* !ICE_NOLOG */

#endif  /* __ICE_LOG_H */
