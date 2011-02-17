/*
 *	brute force TLE
 */
#include <stdio.h>
#include <math.h>

typedef struct _ZeroTrunk {
	int start;
	int size;
	struct _ZeroTrunk *next;
} ZeroTrunk;

int IN[1000][2];

int encode(int n, int width, int total);
int getcode(int n);

int
main()
{
	int width,i,n,cnt,total,current;
	ZeroTrunk Zeros, *p;
	Zeros.next = NULL;
 	
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
	 	
	 	// get zero trunks
	 	cnt = i;
	 	n = 0;
	 	p = &Zeros;
	 	for(i=0; i<cnt; i++) {
	 		int x,y;
	 		
	 		if(IN[i][1] > 2 * width) {
		 		x = (n/width + 1) * width - n;
		 		y = (IN[i][1]- x) % width + 1;
		 		
		 		if(IN[i][1] > x+y+2*width) {
		 			while(p->next != NULL) {
			 			p = p->next;
			 		}
			 		p->next = (ZeroTrunk *)malloc(sizeof(ZeroTrunk));
			 		p->next->start = n + x + width + 1;
			 		p->next->size = IN[i][1] - x - y - 2 * width;
			 		p->next->next = NULL;
		 		}
		 	}
		 	n += IN[i][1];
	 	}
	 	
 		printf("%d\n", width);
	 	
	 	// calculate
	 	cnt = 1;
	 	current = encode(1, width, total);
	 	for(i=2; i<=total; i++) {
	 		if(Zeros.next && i == Zeros.next->start) {
		 		if(current == 0) {
 			 		cnt += Zeros.next->size;
		 		} else {
		 			printf("%d %d\n", current, cnt);
		 			cnt = Zeros.next->size;
		 			current = 0;
		 		}
		 		
		 		i += Zeros.next->size - 1; // for i++
		 		
		 		p = Zeros.next;
		 		Zeros.next = p->next;
		 		free(p);
		 		
		 		continue;
		 	}
	 		
	 		if(current == encode(i, width, total)) {
		 		cnt++;
		 	} else {
	 			printf("%d %d\n", current, cnt);
	 			cnt = 1;
	 			current = encode(i, width, total);
	 		}
		}
	 	printf("%d %d\n", current, cnt);
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
