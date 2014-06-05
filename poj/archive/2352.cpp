#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define SIZE 32001

int a[SIZE + 1];
int c[SIZE + 1];

int lowbit(int t)
{
    return ((-t) & t);
}

int sum(int end)
{
    int sum = 0;
    while(end > 0) {
        sum += c[end];
        end -= lowbit(end);
    }
    return sum;
}

void add(int pos, int val)
{
    while(pos <= SIZE) {
        c[pos] += val;
        pos += lowbit(pos);
    }
}

int main()
{
    int i, n, x, y;
    while(scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof(int) * (SIZE + 1));
        memset(c, 0, sizeof(int) * (SIZE + 1));
        for (i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            x++;
            a[sum(x)]++;
            add(x, 1);
        }
        for(i = 0; i < n; i++)
            printf("%d\n", a[i]);
    }
    return 0;
}
