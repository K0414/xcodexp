/* 
 *		1) 用分治求逆序数适用于无重复字符的情况 
 *		2) struct是可以直接用=赋值的，效果同memcpy 
 *		3) 冒泡排序的多种形式 
 */
 
#include <stdio.h>

#define USEDC 0

#if USEDC
	#define COUNT count_dc
#else
	#define COUNT count
#endif

typedef struct _Node {
	char seq[100];
	int cnt;
} Node;

char L[100],R[100];

// 分治法计算逆序数，适用于无重复字符的情况，复杂度O(nlgn) 
int count_dc(char *str, int l, int r);
int merge_count(char *str, int p, int q, int r); 

// 常规方法计算逆序数 ，复杂度O(n*n) 
int count(char *str, int l, int r);

void sort(Node *list, int n);

int main()
{
	int i,n,len;
	Node list[100];
	char tmp[100];
	
	scanf("%d%d", &len, &n);
	
	for(i=0; i<n; i++) {
		scanf("%s", list[i].seq);
		// copy for seq change
		memcpy(tmp, list[i].seq, 100*sizeof(char));
		list[i].cnt = COUNT(tmp, 0, len-1);
		
		//printf("%s : ", list[i].seq);
		//printf("%d\n", COUNT(list[i].seq, 0, len-1));
	}
	
	sort(list, n);
	
	for(i=0; i<n; i++) {
		//printf("%s : %d\n", list[i].seq, list[i].cnt);
		printf("%s\n", list[i].seq);
	}
	
	return 0;
}

void sort(Node *list, int n)
{
	Node tmp;
	int i,j;
	
	for(i=0; i<n-1; i++) {
		for(j=i+1; j<n; j++) {
			if(list[i].cnt > list[j].cnt) {
				tmp = list[j];
				list[j] = list[i];
				list[i] = tmp;
			}
		}
	}
}

int count(char *str, int l, int r)
{
	int i,j,n,cnt;
	
	n = r - l + 1;
	cnt = 0;
	
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			if(str[l+i] > str[l+j])
				cnt++;
		}
	}
	return cnt;
}

// 分治法计算逆序数 
int count_dc(char *str, int l, int r)
{
	int m,t1,t2;
	
	if(l<r) {
		m = (l+r) / 2;
		t1 = count_dc(str, l, m);
		t2 = count_dc(str, m+1, r);
		return merge_count(str, l, m, r) + t1 + t2;
	}
	
	return 0;
}

int merge_count(char *str, int p, int q, int r)
{
	int n1,n2,i,j,k,cnt;
	char *pt;
	
	pt = str + p;
	n1 = q - p + 1;
	n2 = r - q;
	
	memcpy(L, str+p, n1);
	memcpy(R, str+q+1, n2);
	
	cnt = i = j = k = 0;
	while(i<n1 && j<n2) {
		if(L[i] > R[j]) {
			pt[k++] = R[j++];
			cnt++;
		} else {
			pt[k++] = L[i++];
		}
	}
	
	if(i < n1) {
		for( ; i < n1; i++) {
			pt[k++] = L[i];
			cnt += n2; // 左侧剩余元素均比右侧所有元素大 
		}
		cnt -= n2; // 上步中第一个剩余元素多记了一次 
	}
	
	for( ; j < n2; j++) {
		pt[k++] = R[j];
	}
	
	return cnt;
}
