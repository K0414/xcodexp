#include <stdio.h>

int tab[] = { 	2, 7, 5, 30, 169, 441,
				1872, 7632, 1740, 93313,
				459901, 1358657, 2504881};

int
main()
{
	int k,i,m,flag;
	
	while(scanf("%d", &k)) {		
		if(k == 0)
			break;
		
		printf("%d\n", tab[k-1]);
	}
	
	return 0;
}
