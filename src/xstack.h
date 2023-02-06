/**
 * @file xstack.h
 * @author qylWheels (command1748165360@126.com)
 * @brief FILO data structure.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __XSTACK_H
#define __XSTACK_H 1

#include "xharp.h"
#include <stddef.h>

struct _xstack;
typedef struct _xstack xstack;

__XBEGIN_DECLS

extern xstack *xstack_new(void);

extern xstack *xstack_from(void *first, ...);

extern void xstack_delete(xstack *stk);

extern xstack *xstack_clear(xstack *stk);

extern xstack *xstack_push(xstack *stk, void *data);

extern void *xstack_pop(xstack *stk);

extern void *xstack_top(xstack *stk);

extern size_t xstack_size(xstack *stk);

extern int xstack_empty(xstack *stk);

__XEND_DECLS

#endif  /* !__XSTACK_H */
