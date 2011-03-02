#include <stdio.h>
#include <string.h>

char buf[300];
int pos[300];
int div[300];

int main()
{
	int i,j,n,k,p;
	char tmp[300];
	int t;
	
	while(scanf("%d", &n)) {
		if(n == 0)
			break;

		for(i=0; i<n; i++) {
			scanf("%d", &pos[i]);
			pos[i] -= 1;
		}

		for(i=0; i<n; i++) {
			t = 1;
			p = pos[i];
			while(p != i) {
				t++;
				p = pos[p];
			}
			div[i] = t;
		}
		
		while(scanf("%d", &k)) {
			if(k == 0)
				break;

			getchar(); 			/* 去掉k后的空格 */
			gets(buf);
			for(i=strlen(buf); i<n; i++) {
				buf[i] = 0x20;
			}
			buf[i] = '\0';

			for(i=0; i<n; i++) {
				p = i;
				t = k % div[i];
				for(j=0; j<t; j++) {
					p = pos[p];
				}
				tmp[p] = buf[i];
			}
			tmp[n] = '\0';
			printf("%s\n", tmp);
		}
		printf("\n");
	}
	
	return 0;
}
