#include <stdio.h>

int mod(int n, int m);

int
main()
{
	int n,m;
	
	while(scanf("%d%d", &n, &m) != EOF)
		printf("%d\n", mod(n, m));

	return 0;
}

int mod(int n, int m)
{
	int i = m;
	
	while(i <= n) {
		i += m;
	}
	return n - i + m;
}
