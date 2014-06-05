#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        // Recursive method with pruning.
        //return _check_recursive(s1, s2);

        // DP method.
        return _check_dp(s1, s2);
    }

    bool _check_recursive(string s1, string s2) {
        if (s1.size() != s2.size())
            return false;
        if (s1 == s2)
            return true;

        // Suppose s1 and s2 only consist of lower case alphabets.
        char ccount[26] = { 0 };
        for (int i = 0; i < s1.size(); i++)
            ccount[s1[i] - 'a']++;
        for (int i = 0; i < s2.size(); i++)
            ccount[s2[i] - 'a']--;
        for (int i = 0; i < 26; i++)
            if (ccount[i] != 0)
                return false;

        bool res;
        for (int i = 1; i < s1.size(); i++) {
            // 1) No rotation.
            res = _check_recursive(s1.substr(0, i), s2.substr(0, i))
                  && _check_recursive(s1.substr(i), s2.substr(i));
            if (res) return true;
            // 2) Rotation.
            res = _check_recursive(s1.substr(0, i), s2.substr(s2.size()-i, i))
                  && _check_recursive(s1.substr(i), s2.substr(0, s1.size()-i));
            if (res) return true;
        }
        return false;
    }

    bool _check_dp(string s1, string s2)
    {
        if (s1.size() != s2.size()) return false;
        
        // Preparation for memoization.
        int sl = s1.size() + 1;
        int *pool = (int *) malloc(sizeof(int) * sl * sl * sl);
        int **ptr = (int **) malloc(sizeof(int*) * sl * sl);
        for (int i = 0; i <  sl * sl; i++)
            ptr[i] = &pool[i * sl];
        int ***memo = (int ***) malloc(sizeof(int**) * sl);
        for (int i = 0; i < sl; i++)
            memo[i] = &ptr[i * sl];
        

        // memo[len][i][j] indicates whether substr s1' starting from i
        // and s2' starting from j of length len is scramble.
        int len, i, j, m;
        for (i = 0; i < sl-1; i++) {
            for (j = 0; j < sl-1; j++)
                memo[1][i][j] = (s1[i] == s2[j]);
        }
        for (len = 2; len < sl; len++) {
            for (i = 0; i < sl-len; i++) {
                for (j = 0; j < sl-len; j++) {
                    bool b = false;
                    for (m = 1; m < len; m++) {
                        b = (memo[m][i][j+len-m] && memo[len-m][i+m][j])
                            || (memo[m][i][j] && memo[len-m][i+m][j+m]);
                        if (b) break;
                    }
                    memo[len][i][j] = b;
                }
            }
        }

        bool ret = memo[sl-1][0][0];

        free(memo);
        free(ptr);
        free(pool);

        return ret;
    }
};


bool test(string s1, string s2, bool real)
{
    Solution s;
    bool res = s.isScramble(s1, s2);
    cout << "[\033[1;" << ((res == real) ? "32mPass" : "31mFail") << "\033[0m] "
         << "isScramble(\"" << s1 << "\", \"" << s2 << "\") -> "
         << (res ? "True" : "False") << endl;
    return (res == real);
}

int main()
{
    test("great", "rgtae", true);
    test("great", "rtgae", false);
    test("abb", "bba", true);
    test("abcdefghijklmn", "efghijklmncadb", false);
    test("sqksrqzhhmfmlmqvlbnaqcmebbkqfy", "abbkyfqemcqnblvqmlmfmhhzqrskqs", true);

    return 0;
}
