#include "apue.h"
#include <time.h>

int
main(void)
{
    time_t      caltime;

    if ((caltime = time(NULL)) == -1)
        err_sys("time error");

    printf("%ld\n", caltime);

	caltime &= 0xFFFFFFFF;

	while(caltime) {
		printf("%ld", caltime % 2);
		caltime /= 2;
	}
	printf("\n");

    exit(0);
}

