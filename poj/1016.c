#include <stdio.h>
#include <string.h>

char input[100];
int numbers[16][100]; // numbers[i][0]±£´æÎ»Êı

int iterate(int src[], int dest[], int n);
int equal(int src[], int dest[], int n);

int
main()
{
	int cur,i,n,j,k,done;
	
	while(scanf("%s", input) != EOF) {
		if(strcmp(input, "-1") == 0)
			break;
			
		done = i = 0;
		while(input[i]) {
			numbers[0][i+1] = input[i] - '0';
			i++;
		}
		numbers[0][0] = i;
		
		n = iterate(numbers[0], numbers[1], numbers[0][0]);
		if(numbers[0][0] == n && equal(numbers[0], numbers[1], n)) {
			for(k=1; k<=n; k++)
				printf("%d", numbers[0][k]);
			printf(" is self-inventorying\n");
			continue;
		}

		for(j=2; j<16; j++) {
			if(done)
				break;
		
			n = iterate(numbers[j-1], numbers[j], numbers[j-1][0]);
			if(numbers[j-1][0] == n && equal(numbers[j-1], numbers[j], n)) {
				for(k=1; k<=numbers[0][0]; k++)
					printf("%d", numbers[0][k]);
				printf(" is self-inventorying after %d steps\n", j-1);
				done = 1;
				break;
			}
			
			for(i=0; i<j-1; i++) {
				if(numbers[j][0] == numbers[i][0]
					&& equal(numbers[i], numbers[j], numbers[i][0])) {
					for(k=1; k<=numbers[0][0]; k++)
						printf("%d", numbers[0][k]);
					printf(" enters an inventory loop of length %d\n", j-i);
					done = 1;
					break;
				}
			}
		}
		
		if(done)
			continue;
		
		for(k=1; k<=numbers[0][0]; k++)
			printf("%d", numbers[0][k]);
		printf(" can not be classified after 15 iterations\n");
	}

	return 0;
}

int
iterate(int src[], int dest[], int n)
{
	int i,t;
	int tab[10] = { 0 };
	
	for(i=1; i<=n; i++) {
		tab[src[i]]++;
	}
	
	t = 1;
	for(i=0; i<10; i++) {
		if(tab[i]) {
			if(tab[i]>9) {
				dest[t++] = tab[i] / 10;
				dest[t++] = tab[i] % 10;
			} else {
				dest[t++] = tab[i] % 10;
			}
			dest[t++] = i;
		}
	}
	
	dest[0] = t-1;
	
	return t-1;
}

int
equal(int src[], int dest[], int n)
{
	int i;
	
	for(i=1; i<=n; i++) {
		if(src[i] != dest[i])
			return 0;
	}
	
	return 1;
}
