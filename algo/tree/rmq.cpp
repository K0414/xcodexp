#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

#define SIZE        1024
#define max(a,b)    ((a) > (b) ? (a) : (b))

// RMax[i][j] = max val between A[i] and A[i+2^j]
int RMax[SIZE][SIZE];

void RMQ_pre(int *A, int size)
{
    for(int i = 0; i < size; i++)
        RMax[i][0] = A[i];

    for(int i = 0; i < int(log(size) / log(2)); i++) {
        for(int j = 0; j <= size - (int)pow(2, i); j++) {
            RMax[j][i] = max(RMax[j][i-1], RMax[j + (int)pow(2,i-1)][i-1]);
        }
    }
}

int RMQ(int *A, int i, int j)
{
    int k = int(log(j-i+1) / log(2));
    return max(RMax[i][k], RMax[j-int(pow(2, k))+1][k]);
}

int main()
{
    int arr[SIZE];
    int n, c, j, i;
    n = 0;
    cin >> c;
    while(c != -1 && n < SIZE) {
        arr[n++] = c;
        cin >> c;
    }

    cout << "input i,j:" << endl;
    cin >> i >> j;

    RMQ_pre(arr, n); 
    cout << RMQ(arr, i, j) << endl;

    return 0;
}
