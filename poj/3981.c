#include <stdio.h>

char str[1001];
char output[1001];

int
main()
{
	int i,j;
	while(gets(str)) {
		i = 0;
		j = 0;
		while(str[i]) {
			if(str[i]!='y' || str[i+1]!='o' || str[i+2]!='u') {
				output[j++] = str[i++];
			} else {
				output[j++] = 'w';
				output[j++] = 'e';
				i += 3;
			}
		}
		output[j] = 0;
		printf("%s\n", output);
	}

	return 0;
}
