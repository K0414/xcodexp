#include <stdio.h>

int marbles[6]; 

int split(int num);

int
main()
{
	int i,t,c,sum;
	
	c = 1;
	while(1) {
		sum = 0;
		for(i=0; i<6; i++) {
			scanf("%d", &marbles[i]);
			sum += marbles[i] * (i+1);
		}
		
		if(sum == 0)
			break;
			
		printf("Collection #%d:\n", c++);
		
		if(sum % 2 == 1) {
			printf("Can't be divided.\n\n");
			continue;
		}
			
		if(split(sum / 2)) {
			printf("Can be divided.\n\n");
		} else {
			printf("Can't be divided.\n\n");
		}
	}

	return 0;
}

int
split(int num)
{
	int i,ret;
	
	if(num == 0) {
		return 1;
	} else {
		for(i=5; i>=0; i--) { // 先试大的效率高 
			if(num >= i+1 && marbles[i]) {
				marbles[i]--;
				ret = split(num - i - 1);
				marbles[i]++;
				
				if(ret)
					return ret;
					
				// 一次不行，这个数就不用再试了 
				marbles[i] = 0; 
			}
		}
		
		return 0;
	}
}
