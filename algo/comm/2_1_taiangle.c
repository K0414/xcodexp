#include <stdio.h>

int main() {
    int a,b,c,d,e,f;
    for(a=1; a<=6; a++) {
        for(b=1; b<=6;b++) {
            if(a==b) continue;

            for(c=1; c<=6; c++) {
                if(c==a || c==b) continue;

                for(d=1; d<=6; d++) {
                    if(d==a || d==b
                       || d==c) continue;

                    for(e=1; e<=6; e++) {
                        if(e==a || e==b ||
                           e==c || e==d)
                            continue;

                        for(f=1; f<=6;f++) {
                            if(f==a || f==b ||
                               f==c || f==d ||
                               f==e) continue;

                            if((a+b+c)==(c+d+e) &&
                               (c+d+e)==(e+f+a)) {
                                printf("%4d%4d%4d%4d%4d%4d\n",
                                       a, b, c, d, e, f);
                            }
                        }
                    }
                }
            }
        }
    }
                           
    return 0;
}
