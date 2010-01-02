#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fact(int, unsigned int **);
void add(unsigned int **, unsigned int *);

unsigned int len = 100;

int main() {
        // can't be char, array[0] could be a pretty large number.
    unsigned int *array = (unsigned int *)malloc(len * sizeof(unsigned int));
    
    int i,k,n;
    scanf("%d", &n);

    for(k=1; k<=n; k++) {
        fact(k, &array);
            // printf("%d %d %d\n", k, len, array[0]);
        printf("%2d! = ", k);
        for(i=array[0]; i>0; i--)
            printf("%d", array[i]);
        printf("\n");
    }
    free(array);
    
    return 0;
}

void fact(int n, unsigned int **array) {
    int i,j;

    memset(*array, 0, len * sizeof(unsigned int));
    (*array)[0] = 1;
    (*array)[1] = 1;

    for(i=2; i<=n; i++) {
            // for len expanded occasion.
        unsigned int *ori = (unsigned int *)malloc(len * sizeof(unsigned int));
        memcpy(ori, *array, len * sizeof(unsigned int));
        for(j=i-1; j>0; j--)
            add(array, ori);
        free(ori);
    }
}

void add(unsigned int **array, unsigned int *ori) {
    unsigned int i,t,c = 0;
    for(i=1; i<=(*array)[0]; i++) {
        if(i <= ori[0]) {
            t = (*array)[i] + ori[i] + c;
        } else {
            t = (*array)[i] + c;
        }
        (*array)[i] = t % 10;
        c = t / 10; 
    }
    
    if(c) {
            // check whether array[] is full.
        if((*array)[0] == len-1) {
            len += 100;

            unsigned int *p = (unsigned int *)malloc(len * sizeof(unsigned int));
            memset(p, 0, len);
            memcpy(p, *array, len-100);
            free(*array);
            
            *array = p;
        }
        (*array)[++(*array)[0]] = 1;
    }
}
