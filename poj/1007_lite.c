#include <stdio.h>

typedef struct _Node {
	char seq[100];
	int cnt;
} Node;

int count(char *str, int l, int r);

void sort(Node *list, int n);

int main()
{
	int i,n,len;
	Node list[100];
	
	scanf("%d%d", &len, &n);
	
	for(i=0; i<n; i++) {
		scanf("%s", list[i].seq);
		list[i].cnt = count(list[i].seq, 0, len-1);
	}
	
	sort(list, n);
	
	for(i=0; i<n; i++) {
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
