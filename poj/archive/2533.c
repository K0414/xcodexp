#include <stdio.h>

int seq[1010];
int dp[1010];

int max;

int main()
{
	int i,j,n;
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		scanf("%d", &seq[i]);
	}

	dp[0] = 1;
	for(i=1; i<n; i++) {
		max = 0;
		for(j=0; j<i; j++) {
			if(dp[j] > max && seq[i] > seq[j]) {
				max = dp[j];
			}
		}
		dp[i] = max + 1;
	}

	max = dp[0];
	for(i=1; i<n; i++) {
		if(dp[i] > max)
			max = dp[i];
	}
	
	printf("%d\n", max);
	
	return 0;
}
