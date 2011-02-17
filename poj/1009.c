/*
 *	只需考虑原图中数值发生变化的点 
 */
#include <stdio.h>
#include <math.h>

typedef struct _Ref {
	int index;
	int code;
} Ref;

int IN[1000][2];
Ref OUT[8000];

int encode(int n, int width, int total);
int getcode(int n);

void sort(Ref *list, int n);

int
main()
{
	int width,i,j,m,n,t,k,cnt,total,current,row,col;
	Ref cur;
 	
 	while(scanf("%d", &width) != EOF) {
	 	if(width == 0)
	 		break;
	 	
		// input	
 		i = total = 0;
 		scanf("%d%d", &IN[i][0], &IN[i][1]);
 		while(IN[i][0] != 0 || IN[i][1] != 0) {
 			total += IN[i][1];
			i++;
			scanf("%d%d", &IN[i][0], &IN[i][1]);	
	 	} 
	 	
 		printf("%d\n", width);	
 		
 		cnt = i;
 		n = 1;
 		k = 0;
 		for(m=0; m<=cnt; m++) {
		 	row = (n - 1) / width;
			col = (n - 1) % width;
			
			for(i=row-1; i<=row+1; i++) {
				for(j=col-1; j<=col+1; j++) {
					t = i * width + j;
					if(i<0 || j<0 || j>width-1 || t>total-1)
						continue;
					
					OUT[k].index = t + 1;
					OUT[k++].code = encode(t+1, width, total);						
				}
			}
			n += IN[m][1];
		}
		 
		sort(OUT, k);
		
		cur = OUT[0];
		for(i=0; i<k; i++) {
			if(OUT[i].code == cur.code)
				continue;
				
			printf("%d %d\n", cur.code, OUT[i].index - cur.index);
			cur = OUT[i];
		}
 		
 		printf("%d %d\n", cur.code, total - cur.index + 1);
	 	printf("0 0\n");
 	}
 	printf("0\n");
	
	return 0;
}

// 返回第n个元素的编码，n从1开始 
int
getcode(int n)
{
	int t,i;
	
	i = t = 0;
	while(t < n) {
		t += IN[i++][1];
	}
	
	return IN[i-1][0];
}

// 对第n个元素进行编码，n从1开始 
int
encode(int n, int width, int total)
{
	int i,j,t,code,result,row,col;
	
	code = getcode(n);
	
	row = (n - 1) / width;
	col = (n - 1) % width;
	
	result = 0;
	for(i=row-1; i<=row+1; i++) {
		for(j=col-1; j<=col+1; j++) {
			t = i * width + j;
			if(i<0 || j<0 || j>width-1 || t == n-1 || t>total-1)
				continue;
				
			if(abs(getcode(t+1) - code) > result)
				result = abs(getcode(t+1) - code);
		}
	}
	
	return result;
}

void sort(Ref *list, int n)
{
	Ref tmp;
	int i,j;
	
	for(i=0; i<n-1; i++) {
		for(j=i+1; j<n; j++) {
			if(list[i].index > list[j].index) {
				tmp = list[j];
				list[j] = list[i];
				list[i] = tmp;
			}
		}
	}
}
