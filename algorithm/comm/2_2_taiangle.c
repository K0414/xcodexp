#include <stdio.h>

#define SIDE_N 3
#define LENGTH 3
#define VARS   6

int A,B,C,D,E,F;
int *pt[] = {&A,&B,&C,&D,&E,&F};
int *side[SIDE_N][LENGTH] = {&A,&B,&C,&C,&D,&E,&E,&F,&A};
int side_total[SIDE_N];

int main() {
    int i,j,t,is_equal;
    for(i=0; i<VARS; i++)
        *pt[i] = i+1;

    while(1) {
        for(i=0; i<SIDE_N; i++) {
            t = 0;
            for(j=0; j<LENGTH; j++)
                t += *side[i][j];
            side_total[i] = t;
        }

        for(i=1,is_equal=1; is_equal && i<SIDE_N; i++) {
            if(side_total[i] != side_total[i-1])
                is_equal = 0;
        }

        if(is_equal) {
            for(i=0; i<VARS; i++)
                printf("%4d", *pt[i]);
            printf("\n");
//            scanf("%*c");
        }

        for(i=VARS-1; i>0; i--) {
            if(*pt[i] > *pt[i-1])
                break;
        }

        if(i == 0)
            break;

        for(j=VARS-1; j>=i; j--) {
            if(*pt[j] > *pt[i-1]) {
                t = *pt[i-1];
                *pt[i-1] = *pt[j];
                *pt[j] = t;

                break;
            }
        }

        // lagest(smallest) number
        // exchanges hi-low digit :
        // largest <-> smallest
        for(j=VARS-1; j>i; j--,i++) {
            t = *pt[i];
            *pt[i] = *pt[j];
            *pt[j] = t;
        }
        
		// or use sort.
/*
        for(; i<VARS-1; i++) {
			for(j=VARS-1; j>i; j--) {
                if(*pt[j] < *pt[j-1]) {
                    t = *pt[j];
                    *pt[j] = *pt[j-1];
                    *pt[j-1] = t;
                }
            }
        }
*/
    }
        
    return 0;
}
