#include <iostream>
using namespace std;

#define LEN(a) (sizeof(a) / sizeof(int))

int binarySearch(int a[], int l, int r, int k)
{
    while(l <= r) {
        int mid = (l + r) / 2;
        if(a[mid] == k) {
            return mid;
        } else if(a[mid] > k) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int getFirst(int a[], int l, int r, int k)
{
    while(l <= r) {
//        int mid = (l + r) / 2;
        int mid = l + (r - l) / 2;
        if(a[mid] == k) {
            if((mid > l && a[mid - 1] != k) || mid == l)
                return mid;
            else
                r = mid - 1;
        } else if(a[mid] > k) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int getLast(int a[], int l, int r, int k)
{
    while(l <= r) {
        int mid = (l + r) / 2;
        if(a[mid] == k) {
            if((mid < r  && a[mid + 1] != k) || mid == r)
                return mid;
            else
                l = mid + 1;
        } else if(a[mid] > k) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int cyclicBinarySearch(int a[], int l, int r, int k)
{
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] == k) {
            return mid;
        }
        if(a[mid] >= a[l]) { // left in order
            if(a[l] <= k && k < a[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else { // right in order
            if(a[mid] < k && k <= a[r]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}

int getMini(int a[], int n)
{
    int l = 0;
    int r = n - 1;
    int mid = l;
    while(a[l] > a[r]) {
        if(r - l == 1) {
            mid = r;
            break;
        };
        mid = l + (r - l) / 2;
        if(a[mid] >= a[l]) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return a[mid];
}

pair<int, int> matrixBinarySearch(int a[][4], int n, int k)
{
    int row = 0;
    int col = n - 1;
    while(row >= 0 && col >= 0) {
        if(a[row][col] == k) {
            return make_pair<int, int>(row, col);
        } else if(k > a[row][col]) {
            row++;
        } else {
            col--;
        }
    }
    return make_pair<int, int>(-1, -1);
}

void test_binarySearch()
{
    int array[] = {1,3,4,5,6,7,7,8,9};
    cout << binarySearch(array, 0, LEN(array) - 1, 6) << endl;
}

void test_rangeSearch()
{
    int array[] = {1,3,4,5,6,7,7,8,9};
    cout << getFirst(array, 0, LEN(array) - 1, 7) << ' '
         << getLast(array, 0, LEN(array) - 1, 7) << endl;
}

void test_cyclicBinarySearch()
{
    int array[] = {4,5,6,7,8,9,1,2,3};
    cout << cyclicBinarySearch(array, 0, LEN(array) - 1, 1) << endl;
}

void test_cyclicMini()
{
    int array[] = {4,5,6,7,8,9,1,2,3};
//    int array[] = {4};
    cout << getMini(array, LEN(array)) << endl;
}

void test_matrixBinarySearch()
{
    int array[][4] = { { 1, 2, 8, 9 },
                    { 2, 4, 9, 12 },
                    { 4, 7, 10, 13 },
                    { 6, 8, 11, 15 } };
    pair<int, int> res = matrixBinarySearch(array, 4, 10);
    cout << res.first << "," << res.second << endl;
}

int main()
{
    test_binarySearch();
    test_rangeSearch();
    test_cyclicBinarySearch();
    test_cyclicMini();
    test_matrixBinarySearch();
    return 0;
}
