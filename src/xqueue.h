/**
 * @file xqueue.h
 * @author qylWheels (command1748165360@126.com)
 * @brief FIFO data structure.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __XQUEUE_H
#define __XQUEUE_H 1

#include "xharp.h"
#include <stddef.h>

struct _xqueue;
typedef struct _xqueue xqueue;

__XBEGIN_DECLS

extern xqueue *xqueue_new(void);

extern xqueue *xqueue_from(void *first, ...);

extern void xqueue_delete(xqueue *q);

extern xqueue *xqueue_clear(xqueue *q);

extern xqueue *xqueue_in(xqueue *q, void *data);

extern void *xqueue_out(xqueue *q);

extern void *xqueue_front(xqueue *q);

extern void *xqueue_back(xqueue *q);

extern size_t xqueue_size(xqueue *q);

extern int xqueue_empty(xqueue *q);

__XEND_DECLS

#endif  /* !__XQUEUE_H */
