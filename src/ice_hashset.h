/**
 * @file ice_hashset.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Hashset.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __ICE_HASHSET_H
#define __ICE_HASHSET_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_hashset;
typedef struct _ice_hashset ice_hashset;

__ICE_BEGIN_DECLS

extern ice_hashset *ice_hashset_new(size_t (*hash)(const void *val),
		int (*equal)(const void *a, const void *b));

extern ice_hashset *ice_hashset_from(size_t (*hash)(const void *val),
		int (*equal)(const void *a, const void *b), void *first, ...);

extern void ice_hashset_delete(ice_hashset *hs);

extern void *ice_hashset_foreach(ice_hashset *hs,
		int (*apply)(void *val, void *args), void *args);

extern void **ice_hashset_toarray(ice_hashset *hs, void *end);

extern ice_hashset *ice_hashset_union(ice_hashset *hs1, ice_hashset *hs2);

extern ice_hashset *ice_hashset_inter(ice_hashset *hs1, ice_hashset *hs2);

extern ice_hashset *ice_hashset_minus(ice_hashset *hs1, ice_hashset *hs2);

extern ice_hashset *ice_hashset_diff(ice_hashset *hs1, ice_hashset *hs2);

extern ice_hashset *ice_hashset_clear(ice_hashset *hs);

extern void *ice_hashset_add(ice_hashset *hs, void *val);

extern void *ice_hashset_find(ice_hashset *hs, void *val);

extern void *ice_hashset_remove(ice_hashset *hs, void *val);

extern size_t ice_hashset_size(ice_hashset *hs);

extern int ice_hashset_empty(ice_hashset *hs);

__ICE_END_DECLS

#endif  /* __ICE_HASHSET_H */
