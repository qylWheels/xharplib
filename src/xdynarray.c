/**
 * @file xdynarray.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of xdynarray.
 * @version 0.1.0
 * @date 2023-02-06
 * 
 */

#include "xdynarray.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

struct _xdynarray {
	void **_mem;
	size_t _size;
	size_t _capacity;
};

xdynarray *xdynarray_new(size_t reserve)
{
	xdynarray *darr = malloc(sizeof *darr);
	if (NULL == darr)
		return NULL;
	size_t capacity = 4;
	if (reserve > 4) {
		while (capacity < reserve)
			capacity *= 2;
	}
	darr->_mem = malloc(sizeof(void *) * capacity);
	if (NULL == darr->_mem) {
		free(darr);
		return NULL;
	}
	darr->_size = reserve;
	darr->_capacity = capacity;
}

xdynarray *xdynarray_from(void *first, ...)
{
	xdynarray *darr = xdynarray_new(0);
	
	if (NULL == darr)
		return NULL;
	if (NULL == first)
		return darr;
	if (0 > xdynarray_pushback(darr, first)) {
		xdynarray_delete(darr);
		return NULL;
	}

	va_list ap;
	va_start(ap, first);
	void *elem = NULL;
	while (NULL != (elem = va_arg(ap, void *)))
		if (0 > xdynarray_pushback(darr, elem)) {
			xdynarray_delete(darr);
			va_end(ap);
			return NULL;
		}
	va_end(ap);
	
	return darr;
}

void xdynarray_delete(xdynarray *darr)
{
	assert(NULL != darr);
	free(darr->_mem);
	free(darr);
}

static void _builtin_xdynarray_qsort(xdynarray *darr,
		int (*compare)(const void *a, const void *b),
		long begin, long end)
{
	if (begin >= end)
		return;

	void *pivot = darr->_mem[begin];
	long i = begin;
	long j = end;

	while (i < j) {
		while (i < j && 0 <= compare(darr->_mem[j], pivot))
			j--;
		darr->_mem[i] = darr->_mem[j];
		while (i < j && 0 > compare(darr->_mem[i], pivot))
			i++;
		darr->_mem[j] = darr->_mem[i];
	}
	darr->_mem[i] = pivot;
	_builtin_xdynarray_qsort(darr, compare, begin, i - 1);
	_builtin_xdynarray_qsort(darr, compare, i + 1, end);
}

xdynarray *xdynarray_sort(xdynarray *darr,
		int (*compare)(const void *a, const void *b))
{
	assert(NULL != darr);
	assert(NULL != compare);
	_builtin_xdynarray_qsort(darr, compare,
			(long)0, (long)darr->_size - 1);
	return darr;
}

int xdynarray_resize(xdynarray *darr, size_t newsize)
{
	assert(NULL != darr);

	if (newsize <= darr->_capacity) {
		darr->_size = newsize;
		return 1;
	}

	size_t newcapacity = darr->_capacity;
	while (newcapacity < newsize)
		newcapacity *= 2;

	void *newmem = realloc(darr->_mem, sizeof(void *) * newcapacity);
	if (NULL == newmem)
		return -1;
	darr->_mem = newmem;
	darr->_size = newsize;
	darr->_capacity = newcapacity;

	return 1;
}

xdynarray *xdynarray_clear(xdynarray *darr)
{
	assert(NULL != darr);
	darr->_size = 0;
	return darr;
}

void *xdynarray_get(xdynarray *darr, size_t index)
{
	assert(NULL != darr);
	assert(0 <= index && index < darr->_size);

	return darr->_mem[index];
}

xdynarray *xdynarray_put(xdynarray *darr, size_t index,
		void *data)
{
	assert(NULL != darr);
	assert(0 <= index && index < darr->_size);
	assert(NULL != data);

	darr->_mem[index] = data;
	return darr;
}

int xdynarray_pushback(xdynarray *darr, void *data)
{
	assert(NULL != darr);
	assert(NULL != data);
	
	if (0 > xdynarray_resize(darr, darr->_size + 1))
		return -1;
	xdynarray_put(darr, darr->_size - 1, data);
	return 1;
}

void *xdynarray_popback(xdynarray *darr)
{
	assert(NULL != darr);

	if (0 == darr->_size)
		return NULL;
	
	void *ret = darr->_mem[darr->_size - 1];
	--darr->_size;
	return ret;
}

size_t xdynarray_size(xdynarray *darr)
{
	assert(NULL != darr);
	return darr->_size;
}

size_t xdynarray_capacity(xdynarray *darr)
{
	assert(NULL != darr);
	return darr->_capacity;
}

int xdynarray_empty(xdynarray *darr)
{
	assert(NULL != darr);
	return 0 == darr->_size;
}
