#include <stdio.h>
#include <string.h>

char stack[300][110];

int navi(cur);

int main()
{
	memset(stack, 0, 300 * 110 * sizeof(char));
	strcpy(stack[0], "http://www.acm.org/");

	navi(0);
	
	return 0;
}

int navi(int cur)
{
	char cmd[110];
	int i;

	gets(cmd);

	if(cmd[0] == 'Q') {
		return 0;
	} else if(cmd[0] == 'V') {
		strcpy(stack[cur+1], cmd+6);
		printf("%s\n", cmd+6);
		for(i=cur+2; i<300; i++)
			stack[i][0] = 0;
		navi(cur+1);
	} else if(cmd[0] == 'B') {
		if(cur == 0) {
			printf("Ignored\n");
			navi(cur);
		} else {
			printf("%s\n", stack[cur-1]);
			navi(cur-1);
		}
	} else {
		if(stack[cur+1][0] == 0) {
			printf("Ignored\n");
			navi(cur);
		} else {
			printf("%s\n", stack[cur+1]);
			navi(cur+1);
		}
	}
}
