/**
 * @file xhashset.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Hashset.
 * @version 0.1.0
 * @date 2023-01-20
 * 
 */

#ifndef __XHASHSET_H
#define __XHASHSET_H 1

#include "xharp.h"
#include <stddef.h>

struct _xhashset;
typedef struct _xhashset xhashset;

__XBEGIN_DECLS

extern xhashset *xhashset_new(size_t (*hash)(const void *val),
		int (*equal)(const void *a, const void *b));

extern xhashset *xhashset_from(size_t (*hash)(const void *val),
		int (*equal)(const void *a, const void *b), void *first, ...);

extern void xhashset_delete(xhashset *hs);

extern void *xhashset_foreach(xhashset *hs,
		int (*apply)(void *val, void *args), void *args);

extern void **xhashset_toarray(xhashset *hs, void *end);

extern xhashset *xhashset_union(xhashset *hs1, xhashset *hs2);

extern xhashset *xhashset_inter(xhashset *hs1, xhashset *hs2);

extern xhashset *xhashset_minus(xhashset *hs1, xhashset *hs2);

extern xhashset *xhashset_diff(xhashset *hs1, xhashset *hs2);

extern xhashset *xhashset_clear(xhashset *hs);

extern void *xhashset_add(xhashset *hs, void *val);

extern void *xhashset_find(xhashset *hs, void *val);

extern void *xhashset_remove(xhashset *hs, void *val);

extern size_t xhashset_size(xhashset *hs);

extern int xhashset_empty(xhashset *hs);

__XEND_DECLS

#endif  /* !__XHASHSET_H */
