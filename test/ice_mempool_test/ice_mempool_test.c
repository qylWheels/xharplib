#define ICE_DEBUG
#include "../../src/ice_mempool.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *stream = fopen("log.txt", "w");
	ice_mempool *mp = ice_mempool_new();
	void *p = NULL;
	for (int i = 1; i < 10000; i++) {
		p = ice_mempool_calloc(mp, i);
	}
	p = ice_mempool_alloc(mp, 1);
	// ice_mempool_clear(mp);
	ice_mempool_printinfo(stream, mp);
	ice_mempool_delete(mp);
	return 0;
}
