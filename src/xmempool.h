/**
 * @file xmempool.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Memory pool.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __XMEMPOOL_H
#define __XMEMPOOL_H 1

#include "xharp.h"
#include <stddef.h>
#include <stdio.h>

struct _xmempool;
typedef struct _xmempool xmempool;

__XBEGIN_DECLS

extern xmempool *xmempool_new(void);

extern void xmempool_delete(xmempool *mp);

extern void *xmempool_alloc(xmempool *mp, size_t bytes);

extern void *xmempool_calloc(xmempool *mp, size_t bytes);

extern xmempool *xmempool_clear(xmempool *mp);

#ifdef XDEBUG

void xmempool_printinfo(FILE *stream, xmempool *mp);

#endif  /* XDEBUG */

__XEND_DECLS

#endif  /* !__XMEMPOOL_H */
