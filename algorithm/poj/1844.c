#include <stdio.h>

int main()
{
	int i,sum,S;

	scanf("%d", &S);

	sum = i = 0;
	while(sum<S || (sum-S)%2==1)
		sum += ++i;
	
	printf("%d\n", i);
	
	return 0;
}
