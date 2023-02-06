/**
 * @file xlist.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of xlist.
 * @version 0.1.0
 * @date 2023-01-26
 * 
 */

#include "xlist.h"
#include "xmempool.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

struct _xlist {
	xmempool *_mp;
	xlist_node *_first;
	size_t _length;
};

xlist *xlist_new(void)
{
	xlist *l = malloc(sizeof *l);
	if (NULL == l)
		return NULL;
	l->_mp = xmempool_new();
	l->_first = NULL;
	l->_length = 0;
	return l;
}

xlist *xlist_from(void *first, ...)
{
	xlist *l = xlist_new();
	if (NULL == first)
		return l;
	xlist_pushback(l, first);
	
	va_list ap;
	va_start(ap, first);
	void *item = NULL;
	while (NULL != (item = va_arg(ap, void *)))
		xlist_pushback(l, item);
	va_end(ap);

	return l;
}

void xlist_delete(xlist *l)
{
	assert(NULL != l);
	xmempool_delete(l->_mp);
	free(l);
}

xlist_node *xlist_foreach(xlist *l,
		int (*apply)(void *data, void *args), void *args)
{
	assert(NULL != l);
	assert(NULL != apply);

	size_t pos = 0;
	xlist_node *n = NULL;
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

xlist *xlist_reverse(xlist *l)
{
	assert(NULL != l);

	size_t pos = 0;
	xlist_node *n = NULL;
	for (n = l->_first; ++pos <= l->_length; n = n->_prev) {
		xlist_node *tmp = n->_prev;
		n->_prev = n->_next;
		n->_next = tmp;
	}
	l->_first = n->_next;

	return l;
}

void **xlist_toarray(xlist *l, void *end)
{
	assert(NULL != l);

	void **arr = malloc(sizeof(void *) * (l->_length + 1));
	size_t pos = 0;
	xlist_node *n = NULL;
	for (n = l->_first; ++pos <= l->_length; n = n->_next) {
		arr[pos - 1] = n->data;
	}
	arr[pos - 1] = end;

	return arr;
}

xlist *xlist_clear(xlist *l)
{
	assert(NULL != l);

	xmempool_clear(l->_mp);
	l->_first = NULL;
	l->_length = 0;

	return l;
}

xlist_node *xlist_find(xlist *l, void *target,
		int (*equal)(const void *a, const void *b))
{
	assert(NULL != l);
	assert(NULL != target);
	assert(NULL != equal);

	size_t pos = 0;
	xlist_node *n = NULL;
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

void *xlist_erase(xlist_node *n)
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

xlist *xlist_pushfront(xlist *l, void *data)
{
	assert(NULL != l);
	assert(NULL != data);

	xlist_node *n = xmempool_alloc(l->_mp, sizeof *n);
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

void *xlist_front(xlist *l)
{
	assert(NULL != l);
	if (0 == l->_length)
		return NULL;
	else
		return l->_first->data;
}

void *xlist_popfront(xlist *l)
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

xlist *xlist_pushback(xlist *l, void *data)
{
	assert(NULL != l);
	assert(NULL != data);

	xlist_node *n = xmempool_alloc(l->_mp, sizeof *n);
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

void *xlist_back(xlist *l)
{
	assert(NULL != l);
	if (0 == l->_length)
		return NULL;
	else
		return l->_first->_prev->data;
}

void *xlist_popback(xlist *l)
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

size_t xlist_length(xlist *l)
{
	assert(NULL != l);
	return l->_length;
}

int xlist_empty(xlist *l)
{
	assert(NULL != l);
	return 0 == l->_length;
}

