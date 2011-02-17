/*
 *	sprintf(src. "%s%s", src, other)结果不正确，src不能既作源又作目的
 */
#include <stdio.h>
#include <string.h>

typedef struct _Node {
	float value;
	char exp[100];
} Node;

Node tab[4];
int cur;

int solve(int n);

int
main()
{
	int i,t;
	
	for(i=0; i<4; i++) {
		scanf("%d", &t);
		tab[i].value = (float)t;
		sprintf(tab[i].exp, "%d", t);
	}
	
	cur = 0;
	if(solve(4)) {
		printf("%s\n", tab[0].exp);	
	} else {
		printf("no solution.\n");
	}
	
	return 0;
}

int
solve(int n)
{
	int i,j,ret;
	Node tmp[4];
	char str[100];
	
	if(n == 1) {
		if(23.99 < tab[0].value && tab[0].value < 24.01) 
			return 1;
		else
			return 0;
	} else {
		for(i=0; i<n-1; i++) {
			memcpy(tmp, tab, n * sizeof(Node));
			tab[i].value = tab[i].value + tab[i+1].value;
			if(n == 2) {
				sprintf(str, "%s+%s", tab[i].exp, tab[i+1].exp);
			} else {
				sprintf(str, "(%s+%s)", tab[i].exp, tab[i+1].exp);
			}
			strcpy(tab[i].exp, str);
			for(j=i+1; j<n-1; j++) {
				tab[j].value = tab[j+1].value;
				strcpy(tab[j].exp, tab[j+1].exp);
			}
			ret = solve(n-1);
			if(ret) {
				return ret;
			}
			memcpy(tab, tmp, n * sizeof(Node));
	
			tab[i].value = tab[i].value - tab[i+1].value;
			if(n == 2) {
				sprintf(str, "%s-%s", tab[i].exp, tab[i+1].exp);
			} else {
				sprintf(str, "(%s-%s)", tab[i].exp, tab[i+1].exp);
			}
			strcpy(tab[i].exp, str);	
			for(j=i+1; j<n-1; j++) {
				tab[j].value = tab[j+1].value;
				strcpy(tab[j].exp, tab[j+1].exp);
			}
			ret = solve(n-1);
			if(ret) {
				return ret;
			}
			memcpy(tab, tmp, n * sizeof(Node));

			tab[i].value = tab[i].value * tab[i+1].value;
			if(n == 2) {
				sprintf(str, "%s*%s", tab[i].exp, tab[i+1].exp);
			} else {
				sprintf(str, "(%s*%s)", tab[i].exp, tab[i+1].exp);
			}
			strcpy(tab[i].exp, str);
			for(j=i+1; j<n-1; j++) {
				tab[j].value = tab[j+1].value;
				strcpy(tab[j].exp, tab[j+1].exp);
			}
			ret = solve(n-1);
			if(ret) {
				return ret;
			}
			memcpy(tab, tmp, n * sizeof(Node));

			tab[i].value = tab[i].value / tab[i+1].value;
			if(n == 2) {
				sprintf(str, "%s/%s", tab[i].exp, tab[i+1].exp);
			} else {
				sprintf(str, "(%s/%s)", tab[i].exp, tab[i+1].exp);
			}
			strcpy(tab[i].exp, str);
			for(j=i+1; j<n-1; j++) {
				tab[j].value = tab[j+1].value;
				strcpy(tab[j].exp, tab[j+1].exp);
			}
			ret = solve(n-1);
			if(ret) {
				return ret;
			}
			memcpy(tab, tmp, n * sizeof(Node));
		}
		
		return 0;
	}
}
