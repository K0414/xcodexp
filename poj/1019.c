#include <stdio.h>
#include <math.h>

int tab[] = {
	0, 9, 189, 2889, 38889, 488889, 5888889, 68888889, 788888889
};

int current_len;

int calc(int num, int k);
int getlen(int num);

int
main()
{
	int n,r,i,k,t;
	int qu,re;
	
	scanf("%d", &n);
	
	for(i=0; i<n; i++) {
		scanf("%d", &r);

		current_len = 0;
		k = 0;
		t = getlen(++k);
		while(r > t) {
			r -= t;
			t = getlen(++k);
		}
		
		k = 0;
		while(tab[k] < r && k <= 8) {
			k++;
		}
		
		r -= tab[k-1];
		r -= 1;
		
		qu = r / k;
		re = r % k;
		
		printf("%d\n", calc(pow(10,k-1)+qu, k-1-re));
	}
	
	return 0;
}

int
calc(int num, int k)
{
	while(k) {
		num /= 10;
		k--;
	}
	
	return num % 10;
}

int
getlen(int num)
{
	while(num) {
		current_len++;
		num /= 10;
	}
	
	return current_len;
}
