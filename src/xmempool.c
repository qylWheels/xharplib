/**
 * @file xmempool.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of xmempool.
 * @version 0.1.0
 * @date 2023-01-21
 * 
 */

#include "xmempool.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union _xmempool_align_block {
	char _c;
	short _s;
	int _i;
	long _l;
	long long _ll;
	float _f;
	double _d;
	void *_p;
	void (*_pf)(void);
};

struct _xmempool_node {
	struct _xmempool_node *_link;
	union _xmempool_align_block *_base;
	union _xmempool_align_block *_limit;	
};

struct _xmempool {
	struct _xmempool_node *_first;
};

xmempool *xmempool_new(void)
{
	xmempool *newpool = malloc(sizeof *newpool);
	if (NULL == newpool)
		return NULL;
	newpool->_first = NULL;
	return newpool;
}

void xmempool_delete(xmempool *mp)
{
	assert(NULL != mp);
	xmempool_clear(mp);
	free(mp);
}

void *xmempool_alloc(xmempool *mp, size_t bytes)
{
	assert(NULL != mp);
	assert(0 != bytes);

	size_t blksz = sizeof(union _xmempool_align_block);
	size_t blkcnt = (bytes - 1) / blksz + 1;
	int found = 0;
	struct _xmempool_node *n = NULL;
	for (n = mp->_first; NULL != n; n = n->_link) {
		size_t left_blkcnt = n->_limit - n->_base;
		if (left_blkcnt >= blkcnt) {
			found = 1;
			break;
		}
	}

	if (0 == found) {
		n = malloc(sizeof *n + blksz * blkcnt * 2);
		if (NULL == n)
			return NULL;
		n->_link = mp->_first;
		mp->_first = n;
		n->_base = (union _xmempool_align_block *)(n + 1);
		n->_limit = n->_base + blkcnt * 2;
	}
	n->_base += blkcnt;
	return n->_base - blkcnt;
}

void *xmempool_calloc(xmempool *mp, size_t bytes)
{
	assert(NULL != mp);
	assert(0 != bytes);

	void *mem = xmempool_alloc(mp, bytes);
	if (NULL == mem)
		return NULL;
	memset(mem, 0, bytes);
	return mem;
}

xmempool *xmempool_clear(xmempool *mp)
{
	assert(NULL != mp);

	struct _xmempool_node *curr = mp->_first;
	struct _xmempool_node *next = NULL;
	if (NULL == curr)
		return mp;

	while (NULL != curr) {
		next = curr->_link;
		free(curr);
		curr = next;
	}
	mp->_first = NULL;

	return mp;
}

void xmempool_printinfo(FILE *stream, xmempool *mp)
{
	assert(NULL != mp);

	fprintf(stream, "== xmempool debug info ==\n");
	fprintf(stream, "mempool address: %p\n", mp);
	fprintf(stream, "first node address: %p\n\n", mp->_first);

	struct _xmempool_node *n = NULL;
	size_t num = 1;
	for (n = mp->_first; NULL != n; n = n->_link) {
		fprintf(stream, "node %ld info:\n", num);
		fprintf(stream, "  address: %p\n", n);
		fprintf(stream, "  _base: %p\n", n->_base);
		fprintf(stream, "  _limit: %p\n", n->_limit);
		fprintf(stream, "  _next: %p\n", n->_link);
		fprintf(stream, "  %ld block(s) left\n\n",
			n->_limit - n->_base);
		++num;
	}
}
