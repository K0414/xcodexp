#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int board1[110][110];
int board2[110][110];
int points1[1000];
int points2[1000];

int cmp(const void *a, const void *b);
int compare(int *array1, int *array2, int n);

int
main()
{
    int c,i,j,k,t,w,h,n,x,y,cur1,cur2;

    scanf("%d", &c);
    for(i=0; i<c; i++) {
        scanf("%d%d%d", &w, &h, &n);

        memset(board1, 0, 110 * 110 * sizeof(int));
        memset(points1, 0, 1000 * sizeof(int));
        memset(board2, 0, 110 * 110 * sizeof(int));
        memset(points2, 0, 1000 * sizeof(int));
        for(j=0; j<n; j++) {
            scanf("%d%d", &y, &x);
            board1[x][y] = 1;
        }
        for(j=0; j<n; j++) {
            scanf("%d%d", &y, &x);
            board2[x][y] = 1;
        }

        cur1 = cur2 = 0;
        for(j=0; j<h; j++) {
            for(k=0; k<w; k++) {
                if(board1[j][k]) {
                    t = k + 1;
                    while(board1[j][t] && t<w) {
                        points1[cur1]++;
                        t++;
                    }
                    t = k - 1;
                    while(board1[j][t] && t>=0) {
                        points1[cur1]++;
                        t--;
                    }
                    t = j + 1;
                    while(board1[t][k] && t<h) {
                        points1[cur1]++;
                        t++;
                    }
                    t = j - 1;
                    while(board1[t][k] && t>=0) {
                        points1[cur1]++;
                        t--;
                    }
                    points1[cur1]++;
                    cur1++;
                }
                if(board2[j][k]) {
                    t = k + 1;
                    while(board2[j][t] && t<w) {
                        points2[cur2]++;
                        t++;
                    }
                    t = k - 1;
                    while(board2[j][t] && t>=0) {
                        points2[cur2]++;
                        t--;
                    }
                    t = j + 1;
                    while(board2[t][k] && t<h) {
                        points2[cur2]++;
                        t++;
                    }
                    t = j - 1;
                    while(board2[t][k] && t>=0) {
                        points2[cur2]++;
                        t--;
                    }
                    points2[cur2]++;
                    cur2++;
                }
            }
        }

        qsort(points1, n, sizeof(int), cmp);
        qsort(points2, n, sizeof(int), cmp);
        
        if(compare(points1, points2, n)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

	return 0;
}

int
cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int
compare(int *array1, int *array2, int n)
{
    int i;
    for(i=0; i<n; i++) {
        if(array1[i] != array2[i])
            return 0;
    }

    return 1;
}
