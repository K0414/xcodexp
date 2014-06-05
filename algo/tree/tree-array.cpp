#include <iostream>
using namespace std;

#define ARRAY_SIZE 256

int a[ARRAY_SIZE + 1];
int c[ARRAY_SIZE + 1];

int lowbit(int t)
{
    return (t & (t ^ (t - 1))); // or (-t & t);
}

int sum(int end)
{
    int sum = 0;
    while (end > 0) {
        sum += c[end];
        end -= lowbit(end);
    }
    return sum;
}

void add(int pos, int val)
{
    while (pos <= ARRAY_SIZE) {
        c[pos] += val;
        pos += lowbit(pos);
    }
}

int main()
{
    add(5, 1);
    add(105, 1);
    cout << sum(7) << endl;
    return 0;
}
