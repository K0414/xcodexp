#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

char str[512];
char pattern[128];
char prefix[128];

int kmp(char *str, char *pat);

int main()
{
    int t;

    while(1) {
        printf("text: ");
        gets(str);
        printf("pattern: ");
        gets(pattern);
        
        t = kmp(str, pattern);
        if(t != -1) {
            printf(" found : %d\n\n", t);
        } else {
            printf(" not found!\n\n");
        }
    }

    return 0;
}

int compute_prefix_function(char *patt)
{
    int len = strlen(patt);
    int k;

    prefix[0] = 0;
    k = 0; /* NO. of chars that matched. */
    for(int i = 1; i < len; i++) {
        while(k > 0 && patt[i] != patt[k + 1])
            k = prefix[k];

        if(patt[i] == patt[k + 1])
            k++;

        prefix[i] = k;
    }

    return 0;
}

int kmp(char *str, char *pat)
{
    int len = strlen(str);
    int m = strlen(pat);
    int k = 0; /* NO. of chars that matched. */

    for(int i = 0; i < len; i++) {
        while(k > 0 && str[i] != pat[k])
            k = prefix[k];

        if(str[i] == pat[k])
            k++;

        if(k == m) {
            return i - m + 1;
            // k = prefix[k];
        }
    }

    return -1;
}

