#include <stdio.h>

char seq[1010];

int main()
{
	int t,n,i,j;

	scanf("%d", &n);

	for(t=0; t<n; t++) {
		scanf("%s\n", seq);

		i = j = 0;
		while(seq[j]) {
			if(seq[i] != seq[j]) {
				printf("%d%c", j-i, seq[i]);
				i = j;
			}
			j++;
		}
		printf("%d%c\n", j-i, seq[i]);
	}
	
	return 0;
}
