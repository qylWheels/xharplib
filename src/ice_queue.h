/**
 * @file ice_queue.h
 * @author qylWheels (command1748165360@126.com)
 * @brief FIFO data structure.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __ICE_QUEUE_H
#define __ICE_QUEUE_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_queue;
typedef struct _ice_queue ice_queue;

__ICE_BEGIN_DECLS

extern ice_queue *ice_queue_new(void);

extern ice_queue *ice_queue_from(void *first, ...);

extern void ice_queue_delete(ice_queue *q);

extern ice_queue *ice_queue_clear(ice_queue *q);

extern ice_queue *ice_queue_in(ice_queue *q, void *data);

extern void *ice_queue_out(ice_queue *q);

extern void *ice_queue_front(ice_queue *q);

extern void *ice_queue_back(ice_queue *q);

extern size_t ice_queue_size(ice_queue *q);

extern int ice_queue_empty(ice_queue *q);

__ICE_END_DECLS

#endif  /* __ICE_QUEUE_H */
