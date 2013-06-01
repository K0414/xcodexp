#include <stdio.h>

#define MAX_ROW 110
#define MAX_COL 110

int slope[MAX_ROW][MAX_COL];
int m[MAX_ROW][MAX_COL];
int g_row, g_col;

int calc_slope_length(int i, int j);

int main()
{
    int r, c;
    int i, j;
    int max;
    while(scanf("%d%d", &g_row, &g_col) != EOF) {
        for(i = 0; i < g_row; i++) {
            for(j = 0; j < g_col; j++) {
                scanf("%d", &slope[i][j]);
                m[i][j] = -1;
            }
        }

        for(i = 0; i < g_row; i++) {
            for(j = 0; j < g_col; j++) {
                calc_slope_length(i, j);
            }
        }

        max = 0;
        for(i = 0; i < g_row; i++) {
            for(j = 0; j < g_col; j++) {
                if(m[i][j] > max) {
                    max = m[i][j];
                }
            }
        }
        printf("%d\n", max + 1);
    }

    return 0;
}

int calc_slope_length(int i, int j)
{
    int max, t;

    if(m[i][j] != -1) {
        return m[i][j];
    }

    max = 0;
    /* up */
    if(slope[i-1][j]<slope[i][j] && (i-1)>=0) {
        t = calc_slope_length(i-1, j);
        if(1 + t > max)
            max = 1 + t;
    }

    /* right */
    if(slope[i][j+1]<slope[i][j] && (j+1)<g_col) {
        t = calc_slope_length(i, j+1);
        if(1 + t > max)
            max = 1 + t;
    }

    /* down */
    if(slope[i+1][j]<slope[i][j] && (i+1)<g_row) {
        t = calc_slope_length(i+1, j);
        if(1 + t > max)
            max = 1 + t;
    }

    /* left */
    if(slope[i][j-1]<slope[i][j] && (j-1)>=0) {
        t = calc_slope_length(i, j-1);
        if(1 + t > max)
            max = 1 + t;
    }

    m[i][j] = max;
    return max;
}

