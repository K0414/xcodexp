#include <stdio.h>
#include <string.h>

char str[10];

int lcm(int a, int b);
int gcd(int a, int b);

int
main()
{
	int i,a1,b1,a2,b2,a,b,c;
	
	while(gets(str)) {
		a1 = str[0] - '0';
		b1 = str[2] - '0';
		a2 = str[4] - '0';
		b2 = str[6] - '0';	
		
		b = lcm(b1, b2);
		a1 *= b / b1;
		a2 *= b / b2;
		
		if(str[3] == '-') {
			if(a1 < a2) {
				a = a2 - a1;
				c = gcd(a,b);
				if(b/c == 1)
					printf("-%d\n", a/c);
				else
					printf("-%d/%d\n", a/c, b/c);
			} else if(a1 == a2) {
				printf("0\n");
			} else {
				a = a1 - a2;
				c = gcd(a,b);
				if(b/c == 1)
					printf("%d\n", a/c);
				else
					printf("%d/%d\n", a/c, b/c);
			}
		} else {
			a = a2 + a1;
			c = gcd(a,b);
			if(a == 0) {
				printf("0\n");
			}
			else {
				if(b/c == 1)
					printf("%d\n", a/c);
				else
					printf("%d/%d\n", a/c, b/c);
			}
				
		}
	}

	return 0;
}

int
lcm(int a, int b)
{
	int i = a;
	
	while(i % b)
		i += a;
		
	return i;
}

int gcd(int a, int b)
{
	int t,n,m;
	n = a > b ? a : b;
	m = a + b - n;
	
	while(m) {
		t = m;
		m = n % m;
		n = t;
	}
	
	return n;
}
