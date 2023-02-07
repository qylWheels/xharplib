#include "../../src/xdynarray.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	xdynarray *darr = xdynarray_from("xjp", "hjt", "jzm", "dxp", "mzd", NULL);
	printf("%ld\n", xdynarray_size(darr));
	printf("%ld\n", xdynarray_capacity(darr));
	while (!xdynarray_empty(darr)) {
		printf("%s\n", (char *)xdynarray_popback(darr));
	}
	xdynarray_delete(darr);
	return 0;
}
