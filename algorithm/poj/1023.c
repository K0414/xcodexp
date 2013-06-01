#include <stdio.h>

int res[80];

int main()
{
	int t,k,i;
	char s[80];
	long long n;

	scanf("%d", &t);

	while(t--) {
		scanf("%d", &k);
		scanf("%s\n", s);
		scanf("%lld", &n);
		
		for(i=0; i<k; i++) {
			if(n % 2) {
				if(s[k-1-i] == 'n') {
					n += 1;
				} else {
					n -= 1;		/* 保证n为负数时也正确 */
				}
				res[i] = 1;
			} else {
				res[i] = 0;
			}
			n /= 2;
		}

		if(n != 0) {
			printf("Impossible\n");
		} else {
			for(i=k-1; i>=0; i--)
				printf("%d", res[i]);
			printf("\n");
		}
	}
	
	return 0;
}
