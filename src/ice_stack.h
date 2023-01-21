/**
 * @file ice_stack.h
 * @author qylWheels (command1748165360@126.com)
 * @brief FILO data structure.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __ICE_STACK_H
#define __ICE_STACK_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_stack;
typedef struct _ice_stack ice_stack;

__ICE_BEGIN_DECLS

extern ice_stack *ice_stack_new(void);

extern ice_stack *ice_stack_from(void *first, ...);

extern void ice_stack_delete(ice_stack *stk);

extern ice_stack *ice_stack_clear(ice_stack *stk);

extern ice_stack *ice_stack_push(ice_stack *stk, void *data);

extern void *ice_stack_pop(ice_stack *stk);

extern void *ice_stack_top(ice_stack *stk);

extern size_t ice_stack_size(ice_stack *stk);

extern int ice_stack_empty(ice_stack *stk);

__ICE_END_DECLS

#endif  /* __ICE_STACK_H */
