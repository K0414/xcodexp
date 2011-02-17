#include <stdio.h>

int main()
{
	float month,total;
	int i;
	
	total = 0.0;
	for(i=0; i<12; i++) {
		scanf("%f", &month);
		total += month;
	}
	
	total /= 12;
		
	printf("$%.2f\n", total);
	
	return 0;
}
