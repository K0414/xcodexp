#include <stdio.h>

int res[1000];

int main()
{
	int n,t,i;

	while(scanf("%d", &n) != EOF) {
		t = 2;
		i = 0;
		while(n >= t) {
			res[i++] = t;
			n -= t;
			t++;
		}
		t = i;
		while(n > 0) {
			for(i=t-1; i>=0; i--) {
				if(n == 0)
					break;
				res[i]++;
				n--;
			}
		}
		for(i = 0; i < t; i++)
			printf("%d ", res[i]);
		printf("\n");
	}
	
	return 0;
}
