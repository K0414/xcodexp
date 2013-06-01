#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int L[MAX], R[MAX];

typedef struct _PhoneBookNode {
	int number;
	int count;
	struct _PhoneBookNode *next;
} PhoneBookNode;

int		InputToDigit(char c);
void	AddNumberToPhoneBook(PhoneBookNode *list, int num);
int		getCount(int num, PhoneBookNode *list);
void	sort(int *tab, int i, int k);
void	merge(int *tab, int i, int j, int k);

int
main()
{
	int i,k,n,number;
	int noDup = 1;
	char str[1000];
	int *table; 
	
	PhoneBookNode *Head;
	Head = (PhoneBookNode *)malloc(sizeof(PhoneBookNode));
	Head->number = 0;
	Head->count = 0;
	Head->next = NULL;
	
	scanf("%d", &n);
	
	table = (int *)malloc(sizeof(int)*n);
	
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
		
		AddNumberToPhoneBook(Head, number);
	}
	
	// 查找号码表 
	PhoneBookNode *p;
	p=Head;
	
	n=0;
	while(p!=NULL) {
		if(p->count > 1) {
			table[n++] = p->number;

			noDup = 0;
		}
		p = p->next;
	}
	
	if(noDup)
		printf("No duplicates.\n");
	
	sort(table,0,n-1); // !!!here [0..n-1]
	
	for(i=0; i<n; i++) {
		// printf 输出补0 
		printf("%03d-%04d %d\n",table[i]/10000
							,table[i]%10000 
							,getCount(table[i],Head));
	}
	
	return 0;
}

int
getCount(int num, PhoneBookNode *list)
{
	PhoneBookNode *p = list;
	while(p!=NULL) {
		if(p->number == num)
			return p->count;
			
		p = p->next;
	}
	
	return -1;
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
AddNumberToPhoneBook(PhoneBookNode *list, int num)
{
	PhoneBookNode *p;
	p = list;
	
	while(p!=NULL) {
		if(p->number == num) {
			p->count++;
			return;
		}
		p=p->next;
	} 
	
	p = (PhoneBookNode *)malloc(sizeof(PhoneBookNode));
	p->number = num;
	p->count = 1;
	p->next = list->next;
	
	list->next = p;
	
	return;
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
