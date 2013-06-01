#include <stdio.h>

#define LEN 255
#define BND 99

int tab[100][LEN];
int get(int arr[], int t);
void add(int a[], int b[], int c[]);

int
main()
{
	int i,t,bStart;
	int res[LEN];
	
	while(scanf("%d", &t) != EOF) {
		memset(res, 0, LEN * sizeof(int));
		memset(tab, 0, 100 * LEN * sizeof(int));
		
		get(tab[0], t);
		scanf("%d", &t);
		get(tab[1], t);
		scanf("%d", &t);
		get(tab[2], t);
	
		for(i=3; i<=BND; i++) {
			add(tab[i-3], tab[i-2], res);
			add(tab[i-1], res, tab[i]);
		}
		
		bStart = 0;
		for(i=LEN-1; i>=0; i--) {
			if(tab[BND][i] || bStart) {
				bStart = 1;
				printf("%d", tab[BND][i]);
			}
		}
		if(!bStart) {
			printf("0");
		}
		printf("\n");
	}
	
	return 0;
}

void
add(int a[], int b[], int c[])
{
	int i,t,carry;
	
	carry = 0;
	for(i=0; i<LEN; i++) {
		t = a[i] + b[i] + carry;
		c[i] = t % 10;
		carry = t / 10;
	}
}

int
get(int arr[], int t)
{
	int i;

	for(i=0; t; i++) {
		arr[i] = t % 10;
		t /= 10;
	}
}
