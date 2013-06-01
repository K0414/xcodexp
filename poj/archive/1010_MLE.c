#include <stdio.h>

static int stamps[100];
static int customers[1000];

// result[i][4]记录邮票枚数，result[i][5]记录种数 
static int result[1000000][6]; 

void sort(int *list, int n);
int allocate(int total, int stmp_cnt);

int
main()
{
	int i,j,k,t,n_stmp,n_custm,tmp,best,sel,sel_num,sel_type;
	int highest,h;
	
	while(scanf("%d", &t) != EOF) {
		i = 0;
		while(t != 0) {
			stamps[i++] = t;
			scanf("%d", &t);
		}
		n_stmp = i;
		
		i = 0;
		scanf("%d", &t);
		while(t != 0) {
			customers[i++] = t;
			scanf("%d", &t);
		}
		n_custm = i;
		
		for(i=0; i<n_custm; i++) {
			t = allocate(customers[i], n_stmp);
			if(t == 0) { // t is the number of results
				printf("%d ---- none\n", customers[i]);
			} else {
				best = 0;
				sel = -1;
				sel_num = 255;
				sel_type = -1;
				highest = 0;
				
				for(j=0; j<t; j++) {
					sort(result[j],result[j][4]);
				}
					
				t = merge(result, t);
					
				for(j=0; j<t; j++) {	
					// 求邮票种类数 
					result[j][5] = 1;
					tmp = result[j][0];
					for(k=1; k<result[j][4]; k++) {
						if(tmp != result[j][k]) {
							result[j][5]++;
							tmp = result[j][k];
						}
					}

//////////////////////					
					for(k=0; k<result[j][4]; k++) {
						printf("%d ", result[j][k]);
					}					
					printf(": %d\n", result[j][5]);			
///////////////////////	
					
					// 选择最优解
					if(result[j][5] > sel_type) {
						best = 1;
						sel_num = result[j][4];
						sel_type = result[j][5];
						sel = j;
						highest = stamps[result[j][0]];
						for(k=1; k<result[j][4]; k++) {
							if(stamps[result[j][k]] > highest)
								highest = stamps[result[j][k]];
						}
					} else if(result[j][5] == sel_type) {
						if(result[j][4] < sel_num) {
							best = 1;
							sel_num = result[j][4];
							sel_type = result[j][5];
							sel = j;
							highest = stamps[result[j][0]];
							for(k=1; k<result[j][4]; k++) {
								if(stamps[result[j][k]] > highest)
									highest = stamps[result[j][k]];
							}
						} else if(result[j][4] == sel_num) {
							h = stamps[result[j][0]];
							for(k=1; k<result[j][4]; k++) {
								if(stamps[result[j][k]] > h)
									h = stamps[result[j][k]];
							}
							
							if(h > highest) {
								best = 1;
								sel_num = result[j][4];
								sel_type = result[j][5];
								sel = j;
								highest = h;
							} else if(h == highest) {
								best++;
							}
						}
					}
				}
			
				if(best > 1) {
					printf("%d (%d): tie\n", customers[i], result[sel][5]);
				} else {
					printf("%d (%d): ", customers[i], result[sel][5]);
					// need sort?
					for(k=0; k<result[sel][4]; k++)
						printf("%d ", stamps[result[sel][k]]);
					printf("\n");
				}
			}
		}
	}
	
	return 0;
}

void
sort(int *list, int n)
{
	int tmp;
	int i,j;
	
	for(i=0; i<n-1; i++) {
		for(j=i+1; j<n; j++) {
			if(list[i] > list[j]) {
				tmp = list[j];
				list[j] = list[i];
				list[i] = tmp;
			}
		}
	}
}

int
merge(int *list, int n)
{
	int cnt,i,j,t,fSame;
	cnt = n;
	
	for(i=0; i<cnt; i++) {
		for(j=i+1; j<cnt; j++) {
			fSame = 1;
			for(t=0; t<result[j][4]; t++) {
				if(result[j][t] != result[i][t]) {
					fSame = 0;
					break;
				}
			}
			
			if(fSame) {
				for(t=j+1; t<cnt; t++) {
					memcpy(result[t-1], result[t], 6 * sizeof(int));
				}
				
				cnt--;
				j--;
			}
		}
	}
	
	return cnt;
}

int
allocate(int total, int stmp_cnt)
{
	int i,j,k,l,n,cur;
	
	n = total;
	cur = 0;
	for(i=0; i<stmp_cnt; i++) {
		if(stamps[i] <= n) {
			n -= stamps[i];
			
			if(n == 0) {
				result[cur][0] = i;
				result[cur++][4] = 1;
				n += stamps[i];
				continue; 
			}
			
			for(j=0; j<stmp_cnt; j++) {
				if(stamps[j] <= n) {
					n -= stamps[j];
					
					if(n == 0) {
						result[cur][0] = i;
						result[cur][1] = j;
						result[cur++][4] = 2;
						n += stamps[j];
						continue; 
					}
					
					for(k=0; k<stmp_cnt; k++) {
						if(stamps[k] <= n) {
							n -= stamps[k];
							
							if(n == 0) {
								result[cur][0] = i;
								result[cur][1] = j;
								result[cur][2] = k;
								result[cur++][4] = 3;
								n += stamps[k];
								continue; 
							}
							
							for(l=0; l<stmp_cnt; l++) {
								if(stamps[l] == n) {
									result[cur][0] = i;
									result[cur][1] = j;
									result[cur][2] = k;
									result[cur][3] = l;
									result[cur++][4] = 4;
								}
							}
							n += stamps[k];
						}
					}
					n += stamps[j];
				}
			}
			n += stamps[i];
		}
	}
	
	return cur;
}
