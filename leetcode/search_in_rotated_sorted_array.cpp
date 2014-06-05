#include <iostream>
using namespace std;

class Solution {
public:
    int search(int A[], int n, int target) {
        int l = 0;
        int r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (A[mid] > A[r])
                if (A[mid] < target || target < A[l])
                    l = mid + 1;
                else if (A[mid] > target)
                    r = mid - 1;
                else
                    return mid;
            else
                if (A[mid] > target || target > A[r])
                    r = mid - 1;
                else if (A[mid] < target)
                    l = mid + 1;
                else
                    return mid;
        }
        return -1;
    }
};

bool test(int A[], int n, int target, int real)
{
    Solution sol;
    int res = sol.search(A, n, target);
    cout << "[\033[1;" << ((res == real) ? "32mPass" : "31mFail") << "\033[0m] "
         << "search([ ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << "], " << target << ") -> " << res << endl;
}

int main()
{
    int A1[] = {0,1,2,3,4,5,6,7};
    test(A1, sizeof(A1) / sizeof(int), 3, 3);
    int A2[] = {1,2,3,4,5,6,7,0};
    test(A2, sizeof(A2) / sizeof(int), 3, 2);
    int A3[] = {2,3,4,5,6,7,0,1};
    test(A3, sizeof(A3) / sizeof(int), 3, 1);
    int A4[] = {3,4,5,6,7,0,1,2};
    test(A4, sizeof(A4) / sizeof(int), 3, 0);
    int A5[] = {4,5,6,7,0,1,2,3};
    test(A5, sizeof(A5) / sizeof(int), 3, 7);
    int A6[] = {5,6,7,0,1,2,3,4};
    test(A6, sizeof(A6) / sizeof(int), 3, 6);
    int A7[] = {6,7,0,1,2,3,4,5};
    test(A7, sizeof(A7) / sizeof(int), 3, 5);
    int A8[] = {7,0,1,2,3,4,5,6};
    test(A8, sizeof(A8) / sizeof(int), 3, 4);
    int A9[] = {0,1,2,3,4,5,6,7};
    test(A9, sizeof(A9) / sizeof(int), 9, -1);
    int A10[] = {3,4,5,6,7,0,1,2};
    test(A10, sizeof(A10) / sizeof(int), 9, -1);
    return 0;
}
