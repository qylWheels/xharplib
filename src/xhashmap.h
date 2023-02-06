/**
 * @file xhashmap.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Hashmap.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __XHASHMAP_H
#define __XHASHMAP_H 1

#include "xharp.h"
#include <stddef.h>

struct _xhashmap;
typedef struct _xhashmap xhashmap;

__XBEGIN_DECLS

extern xhashmap *xhashmap_new(size_t (*hash)(const void *key),
		int (*equal)(const void *a, const void *b));

extern xhashmap *xhashmap_from(size_t (*hash)(const void *key),
		int (*equal)(const void *a, const void *b),
		void *first_key, void *first_val, ...);

extern void xhashmap_delete(xhashmap *hm);

extern void *xhashmap_foreach(xhashmap *hm,
		int (*apply)(void *key, void *val, void *args), void *args);

extern void **xhashmap_toarray(xhashmap *hm, void *end);

extern xhashmap *xhashmap_clear(xhashmap *hm);

extern void *xhashmap_add(xhashmap *hm, void *key, void *value);

extern void *xhashmap_find(xhashmap *hm, void *key);

extern void *xhashmap_remove(xhashmap *hm, void *key);

extern size_t xhashmap_size(xhashmap *hm);

extern int xhashmap_empty(xhashmap *hm);

__XEND_DECLS

#endif  /* !__XHASHMAP_H */
