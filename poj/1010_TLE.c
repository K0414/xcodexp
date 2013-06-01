#include <stdio.h>

static int stamps[100];
static int customers[1000];

// result[i][4]记录邮票枚数
// result[i][5]记录种数
// result[i][6]记录最大面值 
static int result[1000000][7]; 

int allocate(int total, int stmp_cnt);

void sort(int *list, int n);
int insert(int item[], int cnt, int cur);
int compare(int item1[], int item2[], int cnt);

int
main()
{
	int i,j,k,t,n_stmp,n_custm,tmp,best,sel,sel_num,sel_type;
	int highest;
	int temp[4];
	
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
//////////////////////					
//					for(k=0; k<result[j][4]; k++) {
//						printf("%d ", result[j][k]);
//					}					
//					printf(": %d\n", result[j][5]);			
///////////////////////	
					
					// 选择最优解
					if(result[j][5] > sel_type) {
						best = 1;
						sel_num = result[j][4];
						sel_type = result[j][5];
						sel = j;
						highest = result[j][6];
					} else if(result[j][5] == sel_type) {
						if(result[j][4] < sel_num) {
							best = 1;
							sel_num = result[j][4];
							sel_type = result[j][5];
							sel = j;
							highest = result[j][6];
						} else if(result[j][4] == sel_num) {
							if(result[j][6] > highest) {
								best = 1;
								sel_num = result[j][4];
								sel_type = result[j][5];
								sel = j;
								highest = result[j][6];
							} else if(result[j][6] == highest) {
								best++;
							}
						}
					}
				}
			
				if(best > 1) {
					printf("%d (%d): tie\n", customers[i], result[sel][5]);
				} else {
					printf("%d (%d): ", customers[i], result[sel][5]);
					
					for(k=0; k<result[sel][4]; k++)
						temp[k] = stamps[result[sel][k]];
						
					// need sort?
					//sort(temp, result[sel][4]);
					
					for(k=0; k<result[sel][4]-1; k++)
						printf("%d ", temp[k]);
					printf("%d\n", temp[k]);
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
compare(int item1[], int item2[], int cnt)
{
	int i,fSame;
	
	fSame = 1;
	for(i=0; i<cnt; i++) {
		if(item1[i] != item2[i]) {
			fSame = 0;
			break;
		}
	}
	
	return fSame;
}

int
insert(int item[], int cnt, int cur)
{
	int i,h,fHas,tmp;
	
	fHas = 0;
	for(i=0; i<cur; i++) {
		if(compare(result[i], item, cnt)) {
			fHas = 1;
			break;
		}
	}
	
	if(!fHas) {
		for(i=0; i<cnt; i++) {
			result[cur][i] = item[i];
		}
		result[cur][4] = cnt;
		
		// 求邮票种类数 
		result[cur][5] = 1;
		tmp = result[cur][0];
		for(i=1; i<cnt; i++) {
			if(tmp != result[cur][i]) {
				result[cur][5]++;
				tmp = result[cur][i];
			}
		}
		
		// 求最大面值
		h = stamps[result[cur][0]];
		for(i=1; i<result[cur][4]; i++) {
			if(stamps[result[cur][i]] > h)
				h = stamps[result[cur][i]];
		} 
		result[cur][6] = h;
		
		return cur + 1;
	}
	
	return cur;
}

int
allocate(int total, int stmp_cnt)
{
	int i,j,k,l,n,t,cur,cnt;
	int tmp[4];
	
	n = total;
	cur = 0;
	for(i=0; i<stmp_cnt; i++) {
		if(stamps[i] <= n) {
			n -= stamps[i];
			
			if(n == 0) {
				tmp[0] = i;
				sort(tmp, 1);
				cur = insert(tmp, 1, cur);
				
				n += stamps[i];
				continue; 
			}
			
			for(j=0; j<stmp_cnt; j++) {
				if(stamps[j] <= n) {
					n -= stamps[j];
					
					if(n == 0) {
						tmp[0] = i;
						tmp[1] = j;
						sort(tmp, 2);
						cur = insert(tmp, 2, cur);
						
						n += stamps[j];
						continue; 
					}
					
					for(k=0; k<stmp_cnt; k++) {
						if(stamps[k] <= n) {
							n -= stamps[k];
							
							if(n == 0) {
								tmp[0] = i;
								tmp[1] = j;
								tmp[2] = k;
								sort(tmp, 3);
								cur = insert(tmp, 3, cur);
								
								n += stamps[k];
								continue; 
							}
							
							for(l=0; l<stmp_cnt; l++) {
								if(stamps[l] == n) {
									tmp[0] = i;
									tmp[1] = j;
									tmp[2] = k;
									tmp[3] = l;
									sort(tmp, 4);
									cur = insert(tmp, 4, cur);
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
