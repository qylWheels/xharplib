/**
 * @file xlog.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of xlog.
 * @version 0.1.0
 * @date 2023-01-24
 * 
 */

#include "xlog.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void xlog_setenv(xlog_env *env, const char *path)
{
	assert(NULL != env);
	assert(NULL != path);

	env->_path = path;
}

int (xlog_log)(xlog_env *env, const char *fmt,
		const char *func, const char *file, int line, ...)
{
	assert(NULL != env);
	assert(NULL != fmt);

	FILE *stream = fopen(env->_path, "a");
	if (NULL == stream)
		return -1;

	time_t date_and_time = time(NULL);
	char buf[256] = { 0 };
	strftime(buf, sizeof buf, "%c", localtime(&date_and_time));
	fprintf(stream, "[%s] function \"%s()\" in %s: %d\n",
		buf, func, file, line);

	va_list vas;
	va_start(vas, line);
	vfprintf(stream, fmt, vas);
	va_end(vas);

	fclose(stream);

	return 0;
}
