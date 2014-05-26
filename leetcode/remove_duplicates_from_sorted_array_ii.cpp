#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

class Solution {
public:
    int removeDuplicates(char A[], int n) {
        int idx = 0;
        int cnt = 1;
        for (int i = 1; i < n; i++)
        {
            if (A[i] == A[idx])
            {
                cnt ++;
            }
            else
            {
                cnt = 1;
            }

            if (cnt <= 2)
            {
                idx ++;
                A[idx] = A[i];
            }
        }
        return n ? idx + 1 : 0;
    }
};


int main()
{
    Solution sol;
    char s[1024];
    while(scanf("%s", s) != EOF)
    {
        int e = sol.removeDuplicates(s, strlen(s));
        s[e] = '\0';
        printf("%s\n", s);
    }
    return 0;
}
