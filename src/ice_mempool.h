/**
 * @file ice_mempool.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Memory pool.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __ICE_MEMPOOL_H
#define __ICE_MEMPOOL_H 1

#include "ice.h"
#include <stddef.h>
#include <stdio.h>

struct _ice_mempool;
typedef struct _ice_mempool ice_mempool;

__ICE_BEGIN_DECLS

extern ice_mempool *ice_mempool_new(void);

extern void ice_mempool_delete(ice_mempool *mp);

extern void *ice_mempool_alloc(ice_mempool *mp, size_t bytes);

extern void *ice_mempool_calloc(ice_mempool *mp, size_t bytes);

extern ice_mempool *ice_mempool_clear(ice_mempool *mp);

#ifdef ICE_DEBUG

void ice_mempool_printinfo(FILE *stream, ice_mempool *mp);

#endif  /* ICE_DEBUG */

__ICE_END_DECLS

#endif  /* __ICE_MEMPOOL_H */
