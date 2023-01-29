/**
 * @file ice_list.h
 * @author qylWheels (command1748165360@126.com)
 * @brief Doubly linked list.
 * @version 0.1.0
 * @date 2023-01-19
 * 
 */

#ifndef __ICE_LIST_H
#define __ICE_LIST_H 1

#include "ice.h"
#include <stddef.h>

struct _ice_list;
typedef struct _ice_list ice_list;

struct _ice_list_node {
	void *data;
	ice_list *_container;
	struct _ice_list_node *_prev;
	struct _ice_list_node *_next;
};
typedef struct _ice_list_node ice_list_node;

__ICE_BEGIN_DECLS

extern ice_list *ice_list_new(void);

extern ice_list *ice_list_from(void *first, ...);

extern void ice_list_delete(ice_list *l);

extern ice_list_node *ice_list_foreach(ice_list *l,
		int (*apply)(void *data, void *args), void *args);

extern ice_list *ice_list_reverse(ice_list *l);

extern void **ice_list_toarray(ice_list *l, void *end);

extern ice_list *ice_list_clear(ice_list *l);

extern ice_list_node *ice_list_find(ice_list *l, void *target,
		int (*equal)(const void *a, const void *b));

extern void *ice_list_erase(ice_list_node *n);

extern ice_list *ice_list_pushfront(ice_list *l, void *data);

extern void *ice_list_front(ice_list *l);

extern void *ice_list_popfront(ice_list *l);

extern ice_list *ice_list_pushback(ice_list *l, void *data);

extern void *ice_list_back(ice_list *l);

extern void *ice_list_popback(ice_list *l);

extern size_t ice_list_length(ice_list *l);

extern int ice_list_empty(ice_list *l);

__ICE_END_DECLS

#endif  /* __ICE_LIST_H */
