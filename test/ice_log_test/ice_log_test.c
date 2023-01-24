// #define ICE_NOLOG
#include "../../src/ice_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	ice_log_env e;
	ice_log_setenv(&e, "log.txt");
	int i = 0;
	while (i++ < 10) {
		ice_log_log(&e, "%s\n\n", "C语言天下第一！！！");
		for (int j = 0; j < 1000000000; ++j);
	}
	return 0;
}
