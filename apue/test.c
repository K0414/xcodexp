#include "apue.h"

int
main(void)
{
	void  **ptr;
	int    i;

	ptr = calloc(5, sizeof(void *));

	for(i = 0; i < 5; i++) {
		printf("0x%x 0x%x\n", (unsigned int)(ptr + i), (unsigned int)*(ptr + i));
	}

    exit(0);
}

