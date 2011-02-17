#include <stdio.h>

int band[100][100];
int price[100][100];
int cand[100];
int max[100];

float getrate(int bd, int n_device);

int
main()
{
	int n,i,j,k;
	int n_device,n_cand,max_band,min_band;
	float res,t;
	
	scanf("%d", &n);
	
	for(i=0; i<n; i++) {
		scanf("%d", &n_device);
		
		max_band = 0;
		min_band = 0x7fffffff;
		for(j=0; j<n_device; j++) {
			scanf("%d", &cand[j]);
			max[j] = 0;
			for(k=0; k<cand[j]; k++) {
				scanf("%d%d", &band[j][k], &price[j][k]);
				if(band[j][k] > max[j])
					max[j] = band[j][k];
				if(band[j][k] < min_band)
					min_band = band[j][k];
			}
		}
		
		max_band = max[0];
		for(j=1; j<n_device; j++) {
			if(max[j] < max_band)
				max_band = max[j];
		}
		
		res = 0.0;
		for(k=min_band; k<=max_band; k++) {
			t = getrate(k, n_device);
			if(t > res)
				res = t;
		}
		
		printf("%.3f\n", res);
	}
	
	return 0;
}

float
getrate(int bd, int n_device)
{
	int i,j,min_cost,total;
	float res;
	
	total = 0;
	for(i=0; i<n_device; i++) {
		min_cost = 0x7fffffff;
		for(j=0; j<cand[i]; j++) {
			if(band[i][j] >= bd && price[i][j] < min_cost) {
				min_cost = price[i][j];
			}
		}
		total += min_cost;
	}
	
	return (float)((float)bd / (float)total);
}
