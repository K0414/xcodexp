#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        return match_recusive(s, p, 0);
        //return match_dp(s, p);
    }

    bool match_recusive(const char *s, const char *p, int level) {
        if (*s == '\0' && *p == '\0')
            return true;

//cout << level << "\t" << s <<endl;
//cout << level << "\t" << p <<endl;

        if (*p == '?') {
            if (isMatch(s, p+1, level+1))
                return true;
            if (*s == '\0')
                return false;
            return isMatch(s+1, p+1, level+1);
        } else if (*p == '*') {
            while (*(p+1) == '*')
                p++;
            while(*s && *(p+1) != '?' && *s != *(p+1))
                s++;
            if (isMatch(s, p+1, level+1))
                return true;
            if (*s == '\0')
                return false;
            return isMatch(s+1, p, level+1);
        } else {
            if (*p != *s)
                return false;
            return isMatch(s+1, p+1, level+1);
        }
    }


    bool match_dp(const char *s, const char *p) {
        bool *match = (bool *) malloc(sizeof(bool) * (strlen(s) + 1));
        memset(match, 0, sizeof(match));
        match[0] = true;
        for (int j = 0; j < strlen(p); j++) {
            for (int i = 0; i <= j; i++) {
                if (('*' == p[j] || s[i] == p[j]) && match[i]) {
                    match[i+1] = true;
                }
            }
        }
        return match[strlen(s) + 1];
    }
};

void test(const char *s, const char *p)
{
    Solution sol;
    cout << "isMatch(\"" << s << "\", \"" << p << "\") -> "
         << (sol.isMatch(s, p) ? "True" : "False") << endl;
}

int main()
{
    test("aa", "a");
    test("aa", "aa");
    test("aaa", "aa");
    test("aa", "*");
    test("aa", "a*");
    test("ab", "?*");
    test("aab", "c*a*b");
    test("", "*a*");
    test("aababa", "a*b");
    test("aabab", "a*b");
    test("a", "*b");
    test("a", "?b");
    test("a", "*a");
    test("a", "?a");
    test("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*b");
    test("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaab", "a*b");
    test("aababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "*a*aaaa*bbabb*b*b*aaaaaaaaa*a*ba*bbb*a*ba*bb*bb*a*b*bb");
    test("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "*aa*ba*a*bb*aa*ab*a*aaaaaa*a*aaaa*bbabb*b*b*aaaaaaaaa*a*ba*bbb*a*ba*bb*bb*a*b*bb");
    test("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");

    return 0;
}
