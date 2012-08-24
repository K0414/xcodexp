#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

int partition(char *vec, int l, int r);
int quicksort(char *vec, int l, int r);

int main()
{
    char arr[11] = "8345190627";

    quicksort(arr, 0, strlen(arr) - 1);
    printf("%s\n", arr);

    return 0;
}

int partition(char *vec, int l, int r)
{
    int i, j;
    char p = vec[l];

    i = l + 1;
    for(j = i; j <= r; j++) {
        if(vec[j] < p) {
            swap(vec[j], vec[i]);
            i++;
        }
    }
    swap(vec[l], vec[i - 1]);
    return i - 1;
}

int quicksort(char *vec, int l, int r)
{
    if(l < r) {
        int pivot = partition(vec, l, r);
        quicksort(vec, l, pivot - 1);
        quicksort(vec, pivot + 1, r);
    }

    return 0;
}

