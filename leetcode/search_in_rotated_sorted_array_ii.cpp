#include <iostream>
using namespace std;

class Solution {
public:
    bool search(int A[], int n, int target) {
        int l = 0;
        int r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;  // Avoid overflow.
            if (A[mid] == target)
                return true;
            if (A[mid] > A[r]) {
                if (A[mid] < target || target < A[l])
                    l = mid + 1;
                else if (A[mid] > target)
                    r = mid - 1;
            } else if (A[mid] < A[r]) {
                if (A[mid] > target || target > A[r])
                    r = mid - 1;
                else if (A[mid] < target)
                    l = mid + 1;
            } else {  /* A[mid] == A[r] */
                r--;
            }
//            } else {  /* A[mid] == A[r] */
//                if (_check_diff(A, mid, r, A[mid]))
//                    l = mid + 1;
//                else
//                    r = mid - 1;
//            }
        }
        return false;
    }

    bool _check_diff(int A[], int l, int r, int target) {
        if (l == r)
            return (A[l] != target);

        int mid = (l+r) / 2;
        if (_check_diff(A, l, mid, target))
            return true;
        if (_check_diff(A, mid+1, r, target))
            return true;
        return false;
    }
};

bool test(int A[], int n, int target, bool real)
{
    Solution sol;
    bool res = sol.search(A, n, target);
    cout << "[\033[1;" << ((res == real) ? "32mPass" : "31mFail") << "\033[0m] "
         << "search([ ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << "], " << target << ") -> " << (res?"True":"False") << endl;
}

int main()
{
    int A1[] = {0,1,2,3,4,5,6,7};
    test(A1, sizeof(A1) / sizeof(int), 3, true);
    int A2[] = {1,2,3,4,5,6,7,0};
    test(A2, sizeof(A2) / sizeof(int), 3, true);
    int A3[] = {2,3,4,5,6,7,0,1};
    test(A3, sizeof(A3) / sizeof(int), 3, true);
    int A4[] = {3,4,5,6,7,0,1,2};
    test(A4, sizeof(A4) / sizeof(int), 3, true);
    int A5[] = {4,5,6,7,0,1,2,3};
    test(A5, sizeof(A5) / sizeof(int), 3, true);
    int A6[] = {5,6,7,0,1,2,3,4};
    test(A6, sizeof(A6) / sizeof(int), 3, true);
    int A7[] = {6,7,0,1,2,3,4,5};
    test(A7, sizeof(A7) / sizeof(int), 3, true);
    int A8[] = {7,0,1,2,3,4,5,6};
    test(A8, sizeof(A8) / sizeof(int), 3, true);
    int A9[] = {0,1,2,3,4,5,6,7};
    test(A9, sizeof(A9) / sizeof(int), 9, false);
    int A10[] = {3,4,5,6,7,0,1,2};
    test(A10, sizeof(A10) / sizeof(int), 9, false);
    int A11[] = {2,3,4,5,0,1,2,2,2};
    test(A11, sizeof(A11) / sizeof(int), 1, true);
    int A12[] = {2,3,4,5,6,7,0,0,1};
    test(A12, sizeof(A12) / sizeof(int), 0, true);
    int A13[] = {2,3,4,5,6,7,0,0,1};
    test(A13, sizeof(A13) / sizeof(int), 4, true);
    int A14[] = {1,1,3,1};
    test(A14, sizeof(A14) / sizeof(int), 3, true);
    int A15[] = {3,1,1,1,1};
    test(A15, sizeof(A15) / sizeof(int), 3, true);
    int A16[] = {1,3,1,1,1};
    test(A16, sizeof(A16) / sizeof(int), 3, true);
    int A17[] = {1,1,3,1,1};
    test(A17, sizeof(A17) / sizeof(int), 3, true);
    int A18[] = {1,1,1,3,1};
    test(A18, sizeof(A18) / sizeof(int), 3, true);
    int A19[] = {1,1,1,1,3};
    test(A19, sizeof(A19) / sizeof(int), 3, true);
    return 0;
}
