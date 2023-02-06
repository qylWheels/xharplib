/**
 * @file xlist.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Doubly linked list.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __XLIST_H
#define __XLIST_H 1

#include "xharp.h"
#include <stddef.h>

struct _xlist;
typedef struct _xlist xlist;

struct _xlist_node {
	void *data;
	xlist *_container;
	struct _xlist_node *_prev;
	struct _xlist_node *_next;
};
typedef struct _xlist_node xlist_node;

__XBEGIN_DECLS

extern xlist *xlist_new(void);

extern xlist *xlist_from(void *first, ...);

extern void xlist_delete(xlist *l);

extern xlist_node *xlist_foreach(xlist *l,
		int (*apply)(void *data, void *args), void *args);

extern xlist *xlist_reverse(xlist *l);

extern void **xlist_toarray(xlist *l, void *end);

extern xlist *xlist_clear(xlist *l);

extern xlist_node *xlist_find(xlist *l, void *target,
		int (*equal)(const void *a, const void *b));

extern void *xlist_erase(xlist_node *n);

extern xlist *xlist_pushfront(xlist *l, void *data);

extern void *xlist_front(xlist *l);

extern void *xlist_popfront(xlist *l);

extern xlist *xlist_pushback(xlist *l, void *data);

extern void *xlist_back(xlist *l);

extern void *xlist_popback(xlist *l);

extern size_t xlist_length(xlist *l);

extern int xlist_empty(xlist *l);

__XEND_DECLS

#endif  /* !__XLIST_H */
