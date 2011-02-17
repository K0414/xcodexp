#include <stdio.h>
#include <stdlib.h>

#define MAX		125
#define BASE	6

unsigned int 	result[MAX];
unsigned int	base[BASE];
unsigned int	temp[MAX];

int main()
{
	int				exp,decimal;
	int				i,j,c,outStart,inDec,showPoint;
	unsigned char	input[BASE+1];
	
	while(scanf("%s%d",input,&exp) == 2) {
		// init
		memset(base, 0, sizeof(base));
		memset(result, 0, sizeof(result));
		memset(temp, 0, sizeof(temp));
		j = 0;
		outStart = 0;
		showPoint = 0;
		inDec = 0;
		
		// deal with input
		for(i=0; i<BASE; i++) {
			if(input[BASE-i-1] == '.') {
				decimal = i;
				continue;
			}
			
			base[j++] = input[BASE-i-1] - '0';			
		}
		
		for(i=0; i<BASE; i++) {
			temp[i] = base[i];
		}
		
		// multiply exp times
		for(c=0; c<exp-1; c++) {
			for(i=0; i<MAX; i++) { // temp
				for(j=0; j<BASE; j++) { //base
					result[i+j] += temp[i] * base[j];
				}
			}
			
			for(i=0; i<MAX; i++) {
				result[i+1] += result[i] / 10;
				result[i] = result[i] % 10;
			}
			
			memcpy(temp, result, sizeof(result));
			memset(result, 0, sizeof(result));
		}
		
		memcpy(result, temp, sizeof(result));
		
		// output
		// 计算结果的小数位数 
		decimal *= exp;
		
		for(i=0; i<decimal; i++) {
			if(result[i]) {
				showPoint = 1;
				break;
			}
		}
		
		for(i=0; i<MAX; i++) {
			// 输出小数点
			if(MAX-i == decimal) {
				// 整数情况
				if(!showPoint)
					break;
					 
				outStart = 1;
				printf(".");
			}
			
			if(MAX-i < decimal)
				inDec = 1;			
			
			if(result[MAX-i-1] != 0) {
				outStart = 1;
				printf("%d", result[MAX-i-1]);
			} else {
				// 输出非前导0 
				if(outStart) {
					// 小数尾部无效0不输出 
					if(inDec) {
						c = MAX-i-1;
						while(!result[c] && c>0)
							c--;
						if(c == 0 && !result[0])
							c = -1;
					
						if(c<0)
							break;
					}
					
					printf("%d", result[MAX-i-1]);
				}
			}
		}
		printf("\n");
	}	
	
	return 0;
}
