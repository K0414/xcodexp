#include <stdio.h>
#include <math.h>

#define N 10
#define tw 44

int B[N] = {0};

int w[N] = {1,2,3,4,5,6,7,8,9,10};
int v[N] = {1,2,3,4,5,6,7,8,9,10};

int main() {
    int maxv = 0;
    int _B[N] = {};
    int i,j,t;

    for(i=0; i<pow(2,N); i++) {
        memset(B, 0, N);
        t = i;
        for(j=0; j<N && t; j++) {
            B[j] = t % 2;
            t /= 2;
        }

        int tmp_w = 0;
        int tmp_v = 0;
        for(j=0; j<N; j++) {
            if(B[j]) {
                tmp_w += w[j];
                tmp_v += v[j];
            }

            if(tmp_w<=tw && tmp_w>maxv) {
                maxv = tmp_v;
                for(t=0; t<N; t++)
                    _B[t] = B[t];
            }
        }
    }
    printf("max value : %d\n", maxv);
    for(i=0; i<N; i++) {
        printf("%4d", _B[i]);
    }
    printf("\n");
    
    return 0;
}
