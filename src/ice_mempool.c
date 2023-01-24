/**
 * @file ice_mempool.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of ice_mempool.
 * @version 0.1.0
 * @date 2023-01-21
 * 
 */

#include "ice_mempool.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union _ice_mempool_align_block {
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

struct _ice_mempool_node {
	struct _ice_mempool_node *_link;
	union _ice_mempool_align_block *_base;
	union _ice_mempool_align_block *_limit;	
};

struct _ice_mempool {
	struct _ice_mempool_node *_first;
};

ice_mempool *ice_mempool_new(void)
{
	ice_mempool *newpool = malloc(sizeof *newpool);
	assert(NULL != newpool);
	newpool->_first = NULL;
	return newpool;
}

void ice_mempool_delete(ice_mempool *mp)
{
	assert(NULL != mp);
	ice_mempool_clear(mp);
	free(mp);
}

void *ice_mempool_alloc(ice_mempool *mp, size_t bytes)
{
	assert(NULL != mp);
	assert(0 != bytes);

	size_t blksz = sizeof(union _ice_mempool_align_block);
	size_t blkcnt = (bytes - 1) / blksz + 1;
	int found = 0;
	struct _ice_mempool_node *n = NULL;
	for (n = mp->_first; NULL != n; n = n->_link) {
		size_t left_blkcnt = n->_limit - n->_base;
		if (left_blkcnt >= blkcnt) {
			found = 1;
			break;
		}
	}

	if (0 == found) {
		n = malloc(sizeof *n + blksz * blkcnt * 2);
		assert(NULL != n);
		n->_link = mp->_first;
		mp->_first = n;
		n->_base = (union _ice_mempool_align_block *)(n + 1);
		n->_limit = n->_base + blkcnt * 2;
	}
	n->_base += blkcnt;
	return n->_base - blkcnt;
}

void *ice_mempool_calloc(ice_mempool *mp, size_t bytes)
{
	assert(NULL != mp);
	assert(0 != bytes);

	void *mem = ice_mempool_alloc(mp, bytes);
	memset(mem, 0, bytes);
	return mem;
}

ice_mempool *ice_mempool_clear(ice_mempool *mp)
{
	assert(NULL != mp);

	struct _ice_mempool_node *curr = mp->_first;
	struct _ice_mempool_node *next = NULL;
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

void ice_mempool_printinfo(FILE *stream, ice_mempool *mp)
{
	assert(NULL != mp);

	fprintf(stream, "== ice_mempool debug info ==\n");
	fprintf(stream, "mempool address: %p\n", mp);
	fprintf(stream, "first node address: %p\n\n", mp->_first);

	struct _ice_mempool_node *n = NULL;
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
