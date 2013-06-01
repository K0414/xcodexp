/*
 *	用%g输出浮点型不错，既可以制定有效位数，又可以不输出无效的0
 *	e.g.  "%.9lg"
 *
 *	用"%.9f"可以AC，"%.9lf"则不行！！！！ 
 *	"%lf"用于long double！！！！ 
 */
#include <stdio.h>

double calce(int n);
int fact(int n);

int
main()
{
	int i;
	
	printf("n e\n");
	printf("- -----------\n");	
	printf("0 1\n");
	printf("1 2\n");
	printf("2 2.5\n");
	
	for(i=3; i<10; i++) {
		printf("%d %.9f\n", i, calce(i));
	}

	return 0;
}

double
calce(int n)
{
	int i;
	double result;
	
	result = 0;
	for(i=0; i<=n; i++) {
		result += 1/(double)fact(i);
	}
	
	return result;
}

int
fact(int n)
{
	if(n == 0) {
		return 1;
	} else {
		return n * fact(n-1);
	}
}
