#include <stdio.h>

int maze[5][5];

int path[1000];
int cur;

int walk(int x, int y);

int
main()
{
	int i,j;
	
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			scanf("%d", &maze[i][j]);
		}
	}
	
	cur = 0;
	if(walk(0, 0)) {
		for(i=0; path[i] != 44; i++) {
			printf("(%d, %d)\n", path[i]/10, path[i]%10);
		}
		printf("(4, 4)\n");
	} else {
		printf("no solution.\n");
	}
	
	return 0;
}

int
walk(int x, int y)
{
	int ret;
	
	if(x==4 && y==4) {
		path[cur++] = 44;
		return 1;
	} else {
		if(y < 4 && maze[x][y+1] == 0) {
			path[cur++] = x * 10 + y;
			maze[x][y+1] = 1;
			ret = walk(x, y + 1);
			if(ret)
				return ret;
				
			cur--;
			maze[x][y+1] = 0;
		}
		
		if(x < 4 && maze[x+1][y] == 0) {
			path[cur++] = x * 10 + y;
			maze[x+1][y] = 1;
			ret = walk(x + 1, y);
			if(ret)
				return ret;
				
			cur--;
			maze[x+1][y] = 0;
		}
	
		if(y > 0 && maze[x][y-1] == 0) {
			path[cur++] = x * 10 + y;
			maze[x][y-1] = 1;
			ret = walk(x, y - 1);
			if(ret)
				return ret;
				
			cur--;
			maze[x][y-1] = 0;
		}
	
		if(x > 0 && maze[x-1][y] == 0) {
			path[cur++] = x * 10 + y;
			maze[x-1][y] = 1;
			ret = walk(x - 1, y);
			if(ret)
				return ret;
				
			cur--;
			maze[x-1][y] = 0;
		}
		
		return 0;
	}
}
