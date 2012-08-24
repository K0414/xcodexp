#include <stdio.h>

#define MAXROW  9
#define MAXCOL  9

int map[MAXROW][MAXCOL];

int checkbox(int r, int c, int n);
int sudoku(int n);

int main()
{
    int i, j, c;
    int cnt, in;

    scanf("%d", &cnt);
    while(cnt--) {
        for(i=0; i<MAXROW; i++) {
            scanf("%d", &in);
            for(j=MAXCOL-1; j>=0; j--) {
                map[i][j] = in % 10;
                in /= 10;
            }
        }

        c = 0;
        for(i=0; i<MAXROW; i++) {
            for(j=0; j<MAXCOL; j++) {
                if(map[i][j] == 0)
                    c++;
            }
        }

        if(sudoku(c)) {
            for(i=0; i<MAXROW; i++) {
                for(j=0; j<MAXCOL; j++) {
                    printf("%d", map[i][j]);
                }
                printf("\n");
            }
        } else {
            printf("no solution\n");
        }
    }

    return 0;
}

int sudoku(int n)
{
    int i, j, k, t, f;

    if(n == 0) { // all filled
        return 1;
    } else {
        for(i=0; i<MAXROW; i++) {
            for(j=0; j<MAXCOL; j++) {
                if(map[i][j] != 0) { // already filled
                    continue;
                } else { // not filled yet, try from 1-9
                    for(k=1; k<=9; k++) {
                        f = 0;
                        // have same number on line or column
                        for(t=0; t<9; t++) {
                            if(map[i][t] == k || map[t][j] == k) {
                                f = 1;
                                break;
                            }
                        }
                        if(f)
                            continue;

                        // check box
                        if(!checkbox(i, j, k))
                            continue;

                        map[i][j] = k;
                        if(sudoku(n-1))
                            return 1;
                        map[i][j] = 0;
                    }
                    return 0; // can't fill 1-9 in current box
                }
            }
        }
    }

    return 0;
}

int checkbox(int r, int c, int n)
{
    int i, j, tr, tc;

    tr = r/3*3;
    tc = c/3*3;

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(tr+i == r && tc+j == c)
                continue;

            if(map[tr+i][tc+j] == n)
                return 0;
        }
    }

    return 1;
}

