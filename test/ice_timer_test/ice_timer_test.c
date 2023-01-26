#include "../../src/ice_timer.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	ice_timer tm;
	ice_timer_init(&tm);
	if (-1 == ice_timer_start(&tm))
		return -1;
	for (long i = 0; i < 10000000000; ++i);
	if (-1 == ice_timer_stop(&tm))
		return -1;
	printf("s: %lf\n"
		"ns: %ld\n",
		ice_timer_s(&tm), ice_timer_ns(&tm));
	if (-1 == ice_timer_start(&tm))
		fprintf(stderr, "ni tama meiyou reset timer !\n");
	return 0;
}
