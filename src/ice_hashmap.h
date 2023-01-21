/**
 * @file ice_hashmap.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Hashmap.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __ICE_HASHMAP_H
#define __ICE_HASHMAP_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_hashmap;
typedef struct _ice_hashmap ice_hashmap;

__ICE_BEGIN_DECLS

extern ice_hashmap *ice_hashmap_new(size_t (*hash)(const void *key),
		int (*equal)(const void *a, const void *b));

extern ice_hashmap *ice_hashmap_from(size_t (*hash)(const void *key),
		int (*equal)(const void *a, const void *b),
		void *first_key, void *first_val, ...);

extern void ice_hashmap_delete(ice_hashmap *hm);

extern void *ice_hashmap_foreach(ice_hashmap *hm,
		int (*apply)(void *key, void *val, void *args), void *args);

extern void **ice_hashmap_toarray(ice_hashmap *hm, void *end);

extern ice_hashmap *ice_hashmap_clear(ice_hashmap *hm);

extern void *ice_hashmap_add(ice_hashmap *hm, void *key, void *value);

extern void *ice_hashmap_find(ice_hashmap *hm, void *key);

extern void *ice_hashmap_remove(ice_hashmap *hm, void *key);

extern size_t ice_hashmap_size(ice_hashmap *hm);

extern int ice_hashmap_empty(ice_hashmap *hm);

__ICE_END_DECLS

#endif  /* __ICE_HASHMAP_H */
