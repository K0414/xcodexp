/*
 *	将down交换左右，等价成up，
 *	记录非even情况下两侧的字母出现次数和所有字母总出现次数。 
 *	结果为coins[i][LEFT]或coins[i][RIGHT]等于3-even，
 *	且coins[i][ALL]等于3-even的字母
 */
#include <stdio.h>
#include <string.h>

#define LEFT	0
#define RIGHT	1
#define ALL		2 

char cases[3][100];
int coins[12][3];

void count(int cur, int side);
void solve(int even);

int
main()
{
	int n,m,k;
	int even;
	
	scanf("%d\n", &n);
	
	for(m=0; m<n; m++) {
		for(k=0; k<12; k++) {
			coins[k][LEFT] = 0;
			coins[k][RIGHT] = 0;
			coins[k][ALL] = 0; 
		}
		
		even = 0;
		
		for(k=0; k<3; k++) {
			gets(cases[k]);
			
			if(strstr(cases[k], "up") != NULL) {
				count(k, LEFT);
			} else if(strstr(cases[k], "down") != NULL) {
				count(k, RIGHT);
			} else {
				even++;
			}
			
			count(k, ALL);
		}

		solve(even);
	}

	return 0;
}

void
count(int cur, int side)
{
	int s,i;
	
	s = side;
	i = 0;
	while(cases[cur][i]) {
		if(cases[cur][i] == ' ' && side != ALL)
			s = (side == LEFT) ? RIGHT : LEFT;
		
		if(cases[cur][i] >= 'A' && cases[cur][i] <= 'L') {
			coins[cases[cur][i] - 'A'][s]++;
		}
		i++;
	}
}

void
solve(int even)
{
	int k,t;

	if(even < 3) {
		for(k=0; k<12; k++) {
			if(coins[k][LEFT] == 3-even && coins[k][ALL] == 3-even) {
				printf("%c is the counterfeit coin and it is heavy.\n"
													, (char)('A'+k));
				return;
			}
			
			if(coins[k][RIGHT] == 3-even && coins[k][ALL] == 3-even) {
				printf("%c is the counterfeit coin and it is light.\n"
													, (char)('A'+k));
				return;
			}
		}
	}
}
