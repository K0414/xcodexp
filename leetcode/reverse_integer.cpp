#include <iostream>
using namespace std;

/* It will be better if you perform an overflow check. */
class Solution {
public:
    int reverse(int x) {
        bool sign = (x < 0);
        if (sign) x = -x;
        long long res = 0;
        while (x) {
            res *= 10;
            res += x % 10;
            x /= 10;
        }
        return sign ? -res : res;
    }
};

int main()
{
    Solution s;
    cout << s.reverse(0) << endl;
    cout << s.reverse(1) << endl;
    cout << s.reverse(100) << endl;
    cout << s.reverse(12) << endl;
    cout << s.reverse(123) << endl;
    cout << s.reverse(-1) << endl;
    cout << s.reverse(-100) << endl;
    cout << s.reverse(-12) << endl;
    cout << s.reverse(-123) << endl;
    return 0;
}
