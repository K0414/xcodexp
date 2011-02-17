#include <stdio.h>

int main()
{
	double real,t;
	int n;
	char str[10];
	while(scanf("%s",str)) {
		if(!strcmp("0.00",str))
			break;
		
		t = 0.0;
		n = 2;	
		real = str[0]-'0' + 0.1 * (str[2]-'0')
						+ 0.01 * (str[3]-'0');
		
		while(t < real) {
			t += 1.0/(double)n;
			n++;
		}
		
		printf("%d card(s)\n", n-2);
	}
	return 0;
}
