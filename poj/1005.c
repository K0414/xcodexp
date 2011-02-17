#include <stdio.h>

#define PI 	3.1415926	

int main()
{
	int i,n,t;
	float x,y;
	
	scanf("%d", &n);
	
	for(i=0; i<n; i++) {
		scanf("%f%f", &x, &y);
		t = (int)(PI*(x*x + y*y) / 100);
		t++;
		printf("Property %d: This property will begin eroding in year %d.\n"
																, i+1, t);
	}
		
	printf("END OF OUTPUT.\n");
	
	return 0;
}
