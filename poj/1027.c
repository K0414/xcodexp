#include <stdio.h>
#include <string.h>
#include <math.h>

char board[20][20];
int used[20][20];

int getsize(int x, int y, char color, int flag);
void compact();
int getremain();

int main()
{
	int t,i,j,c;
	int s,max,stp,pos[2];
	int score;

	c = 1;
	scanf("%d", &t);
	while(t--) {
		for(i=9; i>=0; i--) {
			scanf("%s", board[i]);
		}

		printf("Game %d:\n\n", c++);

		score = 0;
		stp = 1;

		while(1) {
			max = 0;
			pos[0] = pos[1] = 0;
			memset(used, 0, 400 * sizeof(int));

			for(j=0; j<15; j++) {
				for(i=0; i<10; i++) {
					if(board[i][j] != 0x20 && !used[i][j]) {
						s = getsize(i, j, board[i][j], 0);
						if(s > max) {
							max = s;
							pos[0] = i;
							pos[1] = j;
						}
					}
				}
			}

			if(max == 0) {
				score += 1000;
				printf("Final score: %d, with %d balls remaining.\n\n",
					   score, getremain());
				break;
			} else if(max == 1) {
				printf("Final score: %d, with %d balls remaining.\n\n",
					   score, getremain());
				break;
			} else {
				printf("Move %d at (%d,%d): ", stp++, pos[0]+1, pos[1]+1);
				printf("removed %d balls of color %c, got %d points.\n",
					   max, board[pos[0]][pos[1]], (int)pow(max-2,2));
				score += (int)pow(max-2, 2);
					/* remove */
				memset(used, 0, 400 * sizeof(int));
				getsize(pos[0], pos[1], board[pos[0]][pos[1]], 1);
				compact();
			}
		}
	}
	
	return 0;
}

/* flag == 1: remove */
int getsize(int x, int y, char color, int flag)
{
	if(board[x][y] != color || used[x][y]
	     || x>9 || x<0
	     || y>14 || y<0) {
		return 0;
	} else {
		used[x][y] = 1;
		if(flag)
			board[x][y] = 0x20;
		return 1 + getsize(x-1, y, color, flag)
			+ getsize(x, y-1, color, flag)
			+ getsize(x+1, y, color, flag)
			+ getsize(x, y+1, color, flag);
	}
}

void compact()
{
	int i,j;
	int start,end;

	for(j=0; j<15; j++) {
		start = 0;
		while(board[start][j] != 0x20)
			start++;

		end = start + 1;
		while(end < 10) {
			if(board[end][j] != 0x20) {
				board[start++][j] = board[end][j];
				board[end][j] = 0x20;
			}
			end++;
		}
	}
	
	start = 0;
	while(board[0][start] != 0x20)
		start++;

	end = start + 1;
	while(end < 15) {
		if(board[0][end] != 0x20){
			for(i=0; i<10; i++) {
				board[i][start] = board[i][end];
				board[i][end] = 0x20;
			}
			start++;
		}
		end++;
	}
}

int getremain()
{
	int remain = 0;
	int i,j;

	for(i=0; i<10; i++) {
		for(j=0; j<15; j++) {
			if(board[i][j] != 0x20)
				remain++;
		}
	}

	return remain;
}
