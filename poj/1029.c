/*
 *  所有不等的case都等价成<，
 *  记录非even情况下两侧的字母出现次数和所有字母总出现次数。 
 *  在左侧或右侧出现的次数等于不平衡的次数
 *  且出现总次数也为不平衡次数的硬币即为假币
 */
#include <stdio.h>
#include <string.h>

#define LEFT    0
#define RIGHT	1
#define ALL     2 

int cases[110][510];
int coins[1010][3];

int main()
{
	int n,k,i,j,p,s;
	int even;
	int tmp[1010];
	char wei;
	int c,ri;
	
	while(scanf("%d%d", &n, &k) != EOF) {
		memset(coins, 0, 1010 * 3 * sizeof(int));
		even = 0;
	
		for(i=0; i<k; i++) {
			scanf("%d", &p);
			s = p * 2;
			for(j=0; j<s; j++) {
				scanf("%d", &tmp[j]);
			}
		
			scanf("\n%c\n", &wei);
			if(wei == '<') {
				for(j=0; j<p; j++) {
					coins[tmp[j]][LEFT]++;
					coins[tmp[j]][ALL]++;

					coins[tmp[j+p]][RIGHT]++;
					coins[tmp[j+p]][ALL]++;
				}
			} else if(wei == '>') {
				for(j=0; j<p; j++) {
					coins[tmp[j]][RIGHT]++;
					coins[tmp[j]][ALL]++;

					coins[tmp[j+p]][LEFT]++;
					coins[tmp[j+p]][ALL]++;
				}
			} else {
				s = 2 * p;
				for(j=0; j<s; j++) {
					coins[tmp[j]][ALL]++;
				}
				even++;
			}
		}

		c = ri = 0;
		for(i=1; i<=n; i++) {
			if(coins[i][ALL] == k-even
			   && (coins[i][LEFT] == coins[i][ALL]
				   || coins[i][RIGHT] == coins[i][ALL])) {
				c++;
				ri = i;
			}
		}

		if(c == 1)
			printf("%d\n", ri);
		else
			printf("0\n");
	}
	return 0;
}
