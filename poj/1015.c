#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 候选人 */
int CAND[200][2];
/* OPT[i][j]表示所有人中取i个人
 * 使得D-P为j的方案中，
 * D+P所能达到的最大值 */
int OPT[50][1000];
/* OPT[i][j]取得最大值时所选的候选人编号 */
int USED[30][1000]; 
/* 存放选择结果 */
int SEL[30];

void select(int n, int m);
int used(int ti, int tj, int tk);
int cmp(const void *a, const void *b);

int
main()
{
	int i,n,m,c;
    int sel, selup, seldown, t, p, d, k;
	
	c = 1;
    while(scanf("%d%d", &n, &m) != EOF) {
		if(m==0 && n==0)
			break;
		
		for(i=0; i<n; i++) {
            scanf("%d%d", &CAND[i][0], &CAND[i][1]);
		}

        memset(OPT, -1, 50000 * sizeof(int));
        memset(USED, -1, 30000 * sizeof(int));
        memset(SEL, -1, 30 * sizeof(int));
        
		select(n, m);
		
		printf("Jury #%d\n", c++);
		
        selup = seldown = 400;

        while(OPT[m][selup] == -1)
            selup++;
        while(OPT[m][seldown] == -1)
            seldown--;

        sel = (selup-400) < (400-seldown) ? selup : seldown;

        if(selup + seldown == 800)
            sel = OPT[m][selup] > OPT[m][seldown] ? selup : seldown;
        
        p = d = 0;
        for(t=m; t>=1; t--) {
            p += CAND[USED[t][sel]][0];
            d += CAND[USED[t][sel]][1];

            k = USED[t][sel];
            SEL[t-1] = k;
            sel -= CAND[k][1] - CAND[k][0];
        }

        printf("Best jury has value %d for prosecution", p);
        printf(" and value %d for defence:\n", d);

        qsort(SEL, m, sizeof(int), cmp);
        
        for(t=0; t<m; t++) {
            printf(" %d", SEL[t] + 1);
        }
        
		printf("\n\n");
	}

	return 0;
}

int
cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int
used(int ti, int tj, int tk)
{
    int i,j,t;

    j = tj;
    for(i=ti; i>=1; i--) {
        if(USED[i][j] == tk)
            return 1;

        t = USED[i][j];
        j -= CAND[t][1] - CAND[t][0];
    }

    return 0;
}

void
select(int n, int m)
{
    int i,j,k,t;

    OPT[0][400] = 0;
    
    for(i=0; i<m; i++) {
        for(j=0; j<=800; j++) {
            if(OPT[i][j] >= 0) {
                for(k=0; k<n; k++) {
                    if(used(i, j, k))
                        continue;

                    t = OPT[i][j] + CAND[k][0] + CAND[k][1];
                    if(t > OPT[i+1][j+CAND[k][1]-CAND[k][0]]) {
                        OPT[i+1][j+CAND[k][1]-CAND[k][0]] = t;
                        USED[i+1][j+CAND[k][1]-CAND[k][0]] = k;
                    }
                }
            }
        }
    }
}
