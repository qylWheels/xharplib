/**
 * @file ice_dynarray.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Dynamic array.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __ICE_DYNARRAY_H
#define __ICE_DYNARRAY_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_dynarray;
typedef struct _ice_dynarray ice_dynarray;

__ICE_BEGIN_DECLS

extern ice_dynarray *ice_dynarray_new(size_t reserve);

extern ice_dynarray *ice_dynarray_from(void *first, ...);

extern void ice_dynarray_delete(ice_dynarray *darr);

extern ice_dynarray *ice_dynarray_sort(ice_dynarray *darr,
		int (*compare)(const void *a, const void *b));

extern ice_dynarray *ice_dynarray_resize(ice_dynarray *darr, size_t newsize);

extern ice_dynarray *ice_dynarray_clear(ice_dynarray *darr);

extern void *ice_dynarray_get(ice_dynarray *darr, size_t index);

extern ice_dynarray *ice_dynarray_put(ice_dynarray *darr, size_t index,
		void *data);

extern ice_dynarray *ice_dynarray_pushback(ice_dynarray *darr, void *data);

extern void *ice_dynarray_popback(ice_dynarray *darr);

extern size_t ice_dynarray_size(ice_dynarray *darr);

extern int ice_dynarray_empty(ice_dynarray *darr);

__ICE_END_DECLS

#endif  /* __ICE_DYNARRAY_H */
