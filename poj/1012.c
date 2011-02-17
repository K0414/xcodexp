#include <stdio.h>

int people[30];

int order(int k, int m);

int
main()
{
	int k,i,m,flag;
	
	while(scanf("%d", &k) != EOF) {		
		if(k == 0)
			break;
		
		m = k + 1;
		while(m) {
			if(m % (2 * k) == 1) {
				m += k;
				continue;
			}

			for(i=0; i<2*k; i++) {
				people[i] = i+1;
			}
			
			if(order(k, m)) {
				printf("%d\n", m);
				break;
			}
			m++;
		}
	}
	
	return 0;
}

int
order(int k, int m)
{
	int c,i,j,t;
	
	c = t = 0;
	for(i=2*k;i>k;i--) {  
		c = (c + m - 1) % i;  
		if(people[c] <= k)
			return 0;
		for(j=c;j<i-1;j++)  
			people[j]=people[j+1];  
	} 
	return 1;
}
