#include <stdio.h>

int
main()
{
	int items[6];
	int i,sum,n,t;
	
	while(1) {
		sum = 0;
		for(i=0; i<6; i++) {
			scanf("%d", &items[i]);
			sum += items[i];
		}
		
		if(sum == 0)
			break;
			
		n = items[5];
		
		n += items[4];
		t = 11 * items[4];
		if(t > items[0])
			t=items[0];
		items[0] -= t;
		
		n += items[3];
		if(5 * items[3] > items[1]) {
			t = 5 * items[3] - items[1];
			t *= 4;
			if(t>items[0]) {
				items[0] = 0;
			} else {
				items[0] -= t;
			}
			items[1] = 0;
		} else {
			items[1] -= 5 * items[3];
		}
		
		n += items[2] / 4;
		switch(items[2]%4) {
			case 1:
				{
					n++;
					if(items[1]>=5) {
						items[1]-=5;
						if(items[0]>=7) {
							items[0] -= 7;
						} else {
							items[0] = 0;
						}
					} else {
						if(items[0]>=(27-4*items[1])) {
							items[0] -= (27-4*items[1]);
						} else {
							items[0] = 0;
						}
						items[1]=0;
					}
				}
				break;
			case 2:
				{
					n++;
					if(items[1]>=3) {
						items[1]-=3;
						if(items[0]>=6) {
							items[0] -= 6;
						} else {
							items[0] = 0;
						}
					} else {
						if(items[0]>=(18-4*items[1])) {
							items[0] -= (18-4*items[1]);
						} else {
							items[0] = 0;
						}
						items[1]=0;
					}
				}
				break;
			case 3:
				{
					n++;
					if(items[1]) {
						items[1]--;
						if(items[0]>=5) {
							items[0] -= 5;
						} else {
							items[0] = 0;
						}
					}
				}
				break;
			default:
				break;
		}
		
		n += items[1] / 9;
		if(items[1]%9) {
			n++;
			if(items[0]>=(36-(items[1]%9)*4))
				items[0] -= (36-(items[1]%9)*4);
			else
				items[0] = 0;
		}
			
		n += items[0] / 36;
		if(items[0]%36)
			n++;
		
		printf("%d\n", n);
	}
	return 0;
}
