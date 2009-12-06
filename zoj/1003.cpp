#include <stdio.h>
#define NUM 100

int balloon[NUM];
int hiwin,lowrong;

void lower_routine(int loscore, int hiscore);
void check(int score);

int main()
{
	int i,hiscore,loscore,tmp;
	
	while(scanf("%d%d",&hiscore,&loscore) != EOF)
	{
		if(hiscore < loscore)
		{
			tmp = hiscore;
			hiscore = loscore;
			loscore = tmp;
		}
		
		hiwin = 0;
		lowrong = 1;
		lower_routine(loscore,hiscore);
		if(lowrong)
		{
			printf("%d\n",hiscore);
			continue;
		}
		printf("%d\n",hiwin?hiscore:loscore);
	}
	
	return 0;
}

void lower_routine(int loscore, int hiscore)
{
	int i,j;
	for(i=1; i<NUM; i++)
	{
		if(loscore == 1)
		{
			lowrong = 0;
			check(hiscore);
			return;
		}
		
		if(!(loscore%(i+1)) && !balloon[i])
		{
			balloon[i] = 1;
			lower_routine(loscore/(i+1),hiscore);
			balloon[i] = 0;
		}
	}	
}

void check(int score)
{
	int i;
	for(i=1; i<NUM; i++)
	{
		if(score == 1)
		{
			hiwin = 1;
			return;
		}
			
		if(!(score%(i+1)) && !balloon[i])
		{
			balloon[i] = 1;
			check(score/(i+1));
			balloon[i] = 0;
		}
	}
}
