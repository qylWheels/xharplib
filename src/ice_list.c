/**
 * @file ice_list.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of ice_list.
 * @version 0.1.0
 * @date 2023-01-26
 * 
 */

#include "ice_list.h"
#include "ice_mempool.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

struct _ice_list {
	ice_mempool *_mp;
	ice_list_node *_first;
	size_t _length;
};

ice_list *ice_list_new(void)
{
	ice_list *l = malloc(sizeof *l);
	if (NULL == l)
		return NULL;
	l->_mp = ice_mempool_new();
	l->_first = NULL;
	l->_length = 0;
	return l;
}

ice_list *ice_list_from(void *first, ...)
{
	ice_list *l = ice_list_new();
	if (NULL == first)
		return l;
	ice_list_pushback(l, first);
	
	va_list ap;
	va_start(ap, first);
	void *item = NULL;
	while (NULL != (item = va_arg(ap, void *)))
		ice_list_pushback(l, item);
	va_end(ap);

	return l;
}

void ice_list_delete(ice_list *l)
{
	assert(NULL != l);
	ice_mempool_delete(l->_mp);
	free(l);
}

ice_list_node *ice_list_foreach(ice_list *l,
		int (*apply)(void *data, void *args), void *args)
{
	assert(NULL != l);
	assert(NULL != apply);

	size_t pos = 0;
	ice_list_node *n = NULL;
	int brk = 0;
	for (n = l->_first; ++pos <= l->_length; n = n->_next) {
		if (apply(n->data, args) < 0) {
			brk = 1;
			break;
		}
	}

	if (0 != brk)
		return n;
	else
		return NULL;
}

ice_list *ice_list_reverse(ice_list *l)
{
	assert(NULL != l);

	size_t pos = 0;
	ice_list_node *n = NULL;
	for (n = l->_first; ++pos <= l->_length; n = n->_prev) {
		ice_list_node *tmp = n->_prev;
		n->_prev = n->_next;
		n->_next = tmp;
	}
	l->_first = n->_next;

	return l;
}

void **ice_list_toarray(ice_list *l, void *end)
{
	assert(NULL != l);

	void **arr = malloc(sizeof(void *) * (l->_length + 1));
	size_t pos = 0;
	ice_list_node *n = NULL;
	for (n = l->_first; ++pos <= l->_length; n = n->_next) {
		arr[pos - 1] = n->data;
	}
	arr[pos - 1] = end;

	return arr;
}

ice_list *ice_list_clear(ice_list *l)
{
	assert(NULL != l);

	ice_mempool_clear(l->_mp);
	l->_first = NULL;
	l->_length = 0;

	return l;
}

ice_list_node *ice_list_find(ice_list *l, void *target,
		int (*equal)(const void *a, const void *b))
{
	assert(NULL != l);
	assert(NULL != target);
	assert(NULL != equal);

	size_t pos = 0;
	ice_list_node *n = NULL;
	int found = 0;
	for (n = l->_first; ++pos <= l->_length; n = n->_next) {
		if (1 == equal(n->data, target)) {
			found = 1;
			break;
		}
	}

	if (0 != found)
		return n;
	else
		return NULL;
}

void *ice_list_erase(ice_list_node *n)
{
	assert(NULL != n);

	n->_prev->_next = n->_next;
	n->_next->_prev = n->_prev;
	--n->_container->_length;

	if (n == n->_container->_first)
		if (0 < n->_container->_length)
			n->_container->_first = n->_next;
		else
			n->_container->_first = NULL;

	return n->data;
}

ice_list *ice_list_pushfront(ice_list *l, void *data)
{
	assert(NULL != l);
	assert(NULL != data);

	ice_list_node *n = ice_mempool_alloc(l->_mp, sizeof *n);
	n->data = data;
	n->_container = l;
	
	if (0 == l->_length) {
		n->_prev = n->_next = n;
	} else {
		n->_prev = l->_first->_prev;
		n->_next = l->_first;
		l->_first->_prev->_next = n;
		l->_first->_prev = n;
	}

	l->_first = n;
	++l->_length;

	return l;
}

void *ice_list_front(ice_list *l)
{
	assert(NULL != l);
	if (0 == l->_length)
		return NULL;
	else
		return l->_first->data;
}

void *ice_list_popfront(ice_list *l)
{
	assert(NULL != l);

	void *ret = NULL;
	if (0 == l->_length)
		return ret;

	ret = l->_first->data;
	l->_first->_prev->_next = l->_first->_next;
	l->_first->_next->_prev = l->_first->_prev;
	l->_first = l->_first->_next;

	if (1 == l->_length)
		l->_first = NULL;
	
	--l->_length;
	return ret;
}

ice_list *ice_list_pushback(ice_list *l, void *data)
{
	assert(NULL != l);
	assert(NULL != data);

	ice_list_node *n = ice_mempool_alloc(l->_mp, sizeof *n);
	n->data = data;
	n->_container = l;

	if (0 == l->_length) {
		n->_prev = n->_next = n;
		l->_first = n;
	} else {
		n->_prev = l->_first->_prev;
		n->_next = l->_first;
		l->_first->_prev->_next = n;
		l->_first->_prev = n;
	}

	++l->_length;

	return l;
}

void *ice_list_back(ice_list *l)
{
	assert(NULL != l);
	if (0 == l->_length)
		return NULL;
	else
		return l->_first->_prev->data;
}

void *ice_list_popback(ice_list *l)
{
	assert(NULL != l);

	void *ret = NULL;
	if (0 == l->_length)
		return ret;

	ret = l->_first->_prev->data;
	l->_first->_prev->_prev->_next = l->_first;
	l->_first->_prev = l->_first->_prev->_prev;

	if (1 == l->_length)
		l->_first = NULL;
	
	--l->_length;
	return ret;
}

size_t ice_list_length(ice_list *l)
{
	assert(NULL != l);
	return l->_length;
}

int ice_list_empty(ice_list *l)
{
	assert(NULL != l);
	return 0 == l->_length;
}

