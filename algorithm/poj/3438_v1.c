#include <stdio.h>

char seq[1010];

int main()
{
	int t,n,i,sum;

	scanf("%d", &n);

	for(t=0; t<n; t++) {
		scanf("%s\n", seq);

		sum = i = 1;
		while(seq[i]) {
			if(seq[i] == seq[i-1]) {
				sum++;
			} else {
				printf("%d%c", sum, seq[i-1]);
				sum = 1;
			}
			i++;
		}
		printf("%d%c\n", sum, seq[i-1]);
	}
	
	return 0;
}
