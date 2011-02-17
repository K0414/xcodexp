#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int L[MAX], R[MAX];

int		InputToDigit(char c);
void	sort(int *tab, int i, int k);
void	merge(int *tab, int i, int j, int k);

int
main()
{
	int i,k,n,number;
	int noDup = 1;
	char str[1000];
	int *table,*p,*t; 
	
	scanf("%d", &n);
	
	p = table = (int *)malloc(sizeof(int)*n);
	
	// 建立号码表 
	for(i=0; i<n; i++) {
		scanf("%s", str);
		k = 0;
		number = 0;
		
		while(str[k]) {
			if(str[k] == '-') {
				k++;
				continue;
			}

			number *= 10;
			number += InputToDigit(str[k]);
			k++;
		}
		
		*p++ = number;
	}
	
	sort(table,0,n-1);
	
	// 查找号码表 
	p = table;
	while(p-table<n-1) {
		t = p;
		while(*p == *t)
			p++;
		
		if(p-t>1) {
			printf("%03d-%04d %d\n",*t/10000
							,*t%10000 
							,p-t);
			noDup = 0;
		}
	}
	
	if(noDup)
		printf("No duplicates.\n");
	
	return 0;
}

int
InputToDigit(char c)
{
	if(c == 'P' || c == 'R' ||c == 'S') {
		return 7;
	} else if(c >= 'A' && c <= 'O') {
		return (c - 'A')/3 + 2;
	} else if(c >= 'T' && c <= 'Y') {
		return (c - 'T')/3 + 8;
	} else if(c >= '0' && c <= '9') {
		return c -'0';
	}
	
	return -1;
}

void
sort(int *tab, int i, int k)
{
	int m;
	
	if(i<k){
		m = (i+k) / 2;
		sort(tab, i, m);
		sort(tab, m+1, k);
		merge(tab, i, m, k);
	}
}

void
merge(int *tab, int i, int j, int k)
{
	int m,n,n1,n2;
	int *p = tab + i;
	
	n1=j-i+1;
	n2=k-j;
	
	memcpy(L, tab+i, n1*sizeof(int));
	memcpy(R, tab+j+1, n2*sizeof(int));
	
	m=n=0;
	
	while(m<n1 && n<n2) {
		if(L[m] < R[n]) {
			*p++ = L[m++];
		} else {
			*p++ = R[n++];
		}
	}
	for( ; m< n1; m++) {
		*p++ = L[m];
	}
	for( ; n< n2; n++) {
		*p++ = R[n];
	}
}
