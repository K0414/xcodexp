/* 
 *		  p+23*t1
 *		= e+28*t2 
 *		= i+33*t3
 */
 
#include <stdio.h>

#define CANDIV(a,b)		((a) % (b) == 0)

int main()
{
	int p,e,i,d,v,c;
	
	c=1;
	while(scanf("%d%d%d%d", &p, &e, &i, &d) != EOF) {
		if(p==-1 && e==-1
	 		&& i==-1 && d==-1)
	 		break;
		
		v = d+1;
		while(!CANDIV(v-i, 33)) v++;
		while(!CANDIV(v-e, 28)) v+=33;
		while(!CANDIV(v-p, 23)) v+=924; // 33*28
		
		printf("Case %d: the next triple peak occurs in %d days.\n", c, v-d);
		c++;
	}
	
	return 0;
}
