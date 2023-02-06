/**
 * @file xlog.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Log status during runtime.
 * @version 0.1.0
 * @date 2023-01-24
 * 
 */

#ifndef __XLOG_H
#define __XLOG_H 1

#include "xharp.h"
#include <stdio.h>

struct _xlog_env {
	const char *_path;
};
typedef struct _xlog_env xlog_env;

__XBEGIN_DECLS

extern void xlog_setenv(xlog_env *env, const char *path);

extern int (xlog_log)(xlog_env *env, const char *fmt,
		const char *func, const char *file, int line, ...);

__XEND_DECLS

#ifdef XNOLOG
# define xlog_log(penv, fmt, ...) ((void)0)
#else  /* XNOLOG */
# define xlog_log(penv, fmt, ...)	\
	xlog_log(penv, fmt, __FUNCTION__, __FILE__,	\
			__LINE__, ##__VA_ARGS__)
#endif  /* !XNOLOG */

#endif  /* !__XLOG_H */
