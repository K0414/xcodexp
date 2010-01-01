#include <stdio.h>

void fact(int, char *);
void add(char *, char *);

int len = 100;

int main() {
    char *array = (char *)malloc(len * sizeof(char));
    
    int i,k,n;
    scanf("%d", &n);

    for(k=1; k<=n; k++) {
        fact(k, array);

        printf("%d! is: ", k);
        for(i=array[0]; i>0; i--)
            printf("%d", array[i]);
        printf("\n");
    }
    
    return 0;
}

void fact(int n, char *array) {
    int i,j;

    memset(array, 0, len * sizeof(char));
    array[0] = 1;
    array[1] = 1;

    for(i=2; i<=n; i++) {
            // for len expanded occasion.
        char *ori = (char *)malloc(len * sizeof(char));
        memcpy(ori, array, len * sizeof(char));
        for(j=i-1; j>0; j--)
            add(array, ori);
        free(ori);
    }
}

void add(char *array, char *ori) {
    char i,t,c = 0;
    for(i=1; i<=array[0]; i++) {
        t = array[i] + ori[i] + c;
        array[i] = t % 10;
        c = t / 10; 
    }

        // TODO: check whether array[] is full.
    if(c)
        array[++array[0]] = 1;
}
