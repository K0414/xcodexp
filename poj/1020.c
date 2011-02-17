#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canCut(int x, int y, int side, int n);
int cmp(const void *a, const void *b);

int cakes[100];
int colums[100];

int
main()
{
	int i,t,s,n,j;
	int squr;
	
	scanf("%d", &t);
	
	for(i=0; i<t; i++) {
		scanf("%d%d", &s, &n);

		squr = 0;
		for(j=0; j<n; j++) {
			scanf("%d", &cakes[j]);
			squr += cakes[j]*cakes[j];
		}
		
		if(squr != s*s) {
			printf("HUTUTU!\n");
			continue;
		}
		
		qsort(cakes, n, sizeof(int), cmp);
		memset(colums, 0, s*sizeof(int));
		
		if(canCut(0, 0, s, n)) {
			printf("KHOOOOB!\n");
		} else {
			printf("HUTUTU!\n");
		}
	}
	
	return 0;
}

int
cmp(const void *a, const void *b)
{
	return *((int *)b) - *((int *)a);
}

int
canCut(int x, int y, int side, int n)
{
	int i,t,r,j;
	int col,min;
	int canput;
	
	if(x==0 && y==side) {
		return 1;
	} else {
		for(i=0; i<n; i++) {
			if(cakes[i] == 0)
				continue;
				
			if(x+cakes[i] > side || y+cakes[i] > side)
				continue;
			
			canput = 1;
			for(j=x+1; j<x+cakes[i]; j++) {
				if(colums[j] > y) {
					canput = 0;
					break;
				}	
			}
			
			if(!canput)
				continue;
				
			t = cakes[i];
			for(j=x; j<x+t; j++)
				colums[j] += t;
			cakes[i] = 0;
			
			// 计算下一个放置位置
			min = 100;
			for(j=0; j<side; j++) {
				if(colums[j] < min) {
					min = colums[j];
					col = j;
				}
			}
			
			r = canCut(col, colums[col], side, n);

			if(r)
				return r;
				
			cakes[i] = t;
			for(j=x; j<x+t; j++)
				colums[j] -= t;
			
			while(cakes[i+1] == t)
				i++;
		}
		
		return 0;
	}
}
