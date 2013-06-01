#include <stdio.h>

int sticks[100];

int cancut(int len, int left, int num, int stk_cnt);
void sort(int *list, int n);

int
main()
{
	int i,n,t,sum,max;
	
	while(scanf("%d", &n) != EOF) {		
		if(n == 0)
			break;
		
		sum = max = 0;
		for(i=0; i<n; i++) {
			scanf("%d", &t);
			sticks[i] = t;
			sum += t;
			if(t > max)
				max = t;
		}
		
		sort(sticks, n);
				
		for(i=max; ; i++) {
			if(sum % i == 0) {
				if(cancut(i, i, sum / i - 1, n)) {
					printf("%d\n", i);
					break;
				}
			}
		}
	}
	
	return 0;
}

// 降序排效率高 
void
sort(int *list, int n)
{
	int tmp;
	int i,j;
	
	for(i=0; i<n-1; i++) {
		for(j=i+1; j<n; j++) {
			if(list[i] < list[j]) {
				tmp = list[j];
				list[j] = list[i];
				list[i] = tmp;
			}
		}
	}
}

// stk_cnt小木棍数，num长棍数，len每根长棍的长度 
int
cancut(int len, int left, int num, int stk_cnt)
{
	int i,j,t,ret;
	
	if(left == 0 && num == 0) {
		return 1;
	} else {
		for(i=0; i<stk_cnt; i++) {			
			if(sticks[i] == 0)
				continue;
			
			t = sticks[i];
			
			if(sticks[i] < left ) {
				sticks[i] = 0;
				ret = cancut(len, left - t, num, stk_cnt);
				sticks[i] = t;
				
				if(ret)
					return ret;
			}
			
			if(sticks[i] == left ) {
				sticks[i] = 0;
				if(num == 0)
					ret = cancut(len, 0, 0, stk_cnt);
				else
					ret = cancut(len, len, num - 1, stk_cnt);
				sticks[i] = t;
				
				if(ret)
					return ret;
			}
			
			// 剪枝1 
			if(sticks[i] == left || left == len)
				return 0;
			
			// 剪枝2 
			while(sticks[i] == t)
				i++;
			i--;
		}
		
		return 0;
	}
}
