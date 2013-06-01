/*
 *	��%g��������Ͳ����ȿ����ƶ���Чλ�����ֿ��Բ������Ч��0
 *	e.g.  "%.9lg"
 *
 *	��"%.9f"����AC��"%.9lf"���У������� 
 *	"%lf"����long double�������� 
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
