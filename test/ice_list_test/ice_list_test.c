#include "../../src/ice_list.h"
#include "../../src/ice_timer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printlist(void *data, void *args)
{
	printf("%s\n", (char *)data);
	return 1;
}

int freelist(void *data, void *args)
{
	free(data);
	return 1;
}

int find(void *data, void *args)
{
	if (0 == strcmp(data, args))
		return -1;
	return 0;
}

int cmp(const void *a, const void *b)
{
	if (0 == strcmp(a, b))
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	ice_list *l = ice_list_new();
	ice_list_pushfront(l, "xjp");
	ice_list_pushfront(l, "hjt");
	ice_list_pushfront(l, "jzm");
	ice_list_pushfront(l, "mzd");
	ice_list_popback(l);
	assert(ice_list_length(l) == 3);
	ice_list_clear(l);
	assert(ice_list_empty(l) == 1);

	ice_list_foreach(l, printlist, NULL);
	ice_list_delete(l);
	return 0;
}
