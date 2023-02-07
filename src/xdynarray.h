/**
 * @file xdynarray.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Dynamic array.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __XDYNARRAY_H
#define __XDYNARRAY_H 1

#include "xharp.h"
#include <stddef.h>

struct _xdynarray;
typedef struct _xdynarray xdynarray;

__XBEGIN_DECLS

extern xdynarray *xdynarray_new(size_t reserve);

extern xdynarray *xdynarray_from(void *first, ...);

extern void xdynarray_delete(xdynarray *darr);

extern xdynarray *xdynarray_sort(xdynarray *darr,
		int (*compare)(const void *a, const void *b));

extern int xdynarray_resize(xdynarray *darr, size_t newsize);

extern xdynarray *xdynarray_clear(xdynarray *darr);

extern void *xdynarray_get(xdynarray *darr, size_t index);

extern xdynarray *xdynarray_put(xdynarray *darr, size_t index,
		void *data);

extern int xdynarray_pushback(xdynarray *darr, void *data);

extern void *xdynarray_popback(xdynarray *darr);

extern size_t xdynarray_size(xdynarray *darr);

extern size_t xdynarray_capacity(xdynarray *darr);

extern int xdynarray_empty(xdynarray *darr);

__XEND_DECLS

#endif  /* !__XDYNARRAY_H */
