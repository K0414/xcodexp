#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

class SolutionAC {
public:
    bool isMatch(const char *s, const char *p) {
        if (!*p && !*s) return true; // both empty, so sad but true
        if (*p == *s) return isMatch(s + 1, p + 1); // match!
        else if (*p == '?' && *s) return isMatch(s + 1, p + 1); // weird match!
        else if (*p == '*') {
            int ret = false;
            while (*p == '*') ++p; // I only need just one starlet ;)
            if (!*p) return true; // ends with star, the Universe can fit into it now!
            while (*s) { // brute force match
                const char *ts = s, *tp = p;
                while ((*ts == *tp || *tp == '?') && *ts) {
                    if (*tp == '*') break;
                    ++ts; ++tp;
                }
                if (!*ts && !*tp) return true; // both empty
                // *tp is * then ok, otherwise no exact match :(
                if (*tp == '*') { 
                    // we don't need to concern ourself with more exact matches as the * would take care of it, 
                    // and for rest brute force matching will be done
                    ret |= isMatch(ts, tp);
                    return ret;
                }
                if (!*ts) return false; // search exhausted yo! p has more than s can handle :O
                ++s;
            }
            return ret;
        } else return false; // WAT
    }
};

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        //return match_recursive(s, p, 0);
        return match_dp(s, p);
        return match_greedy(s, p);
    }

    bool match_recursive(const char *s, const char *p, int level) {
        if (*s == '\0' && *p == '\0')
            return true;

        //cout << level << "\t" << s <<endl;
        //cout << level << "\t" << p <<endl;

        if (*p == '?') {
            if (*s == '\0')
                return false;
            return match_recursive(s+1, p+1, level+1);
        } else if (*p == '*') {
            while (*(p+1) == '*')
                p++;
            while(*s && *(p+1) != '?' && *s != *(p+1))
                s++;
            if (match_recursive(s, p+1, level+1))
                return true;
            if (*s == '\0')
                return false;
            return match_recursive(s+1, p, level+1);
        } else {
            if (*p != *s)
                return false;
            return match_recursive(s+1, p+1, level+1);
        }
    }


    bool match_dp(const char *s, const char *p) {
        int i, j, len_s, len_p;
        len_s = strlen(s);
        len_p = strlen(p);
        i = j = 0;
        for (; p[i]; i++) {
            if (p[i] != '*') j++;
        }
        if (!*s) return (j == 0);
        if (j > len_s) return false;

        bool *pool = (bool *) malloc(sizeof(bool) * 2 * (len_p + 1));
        bool **memo = (bool **) malloc(sizeof(bool*) * 2);
        for (i = 0; i < 2; i++) memo[i] = &pool[i * (len_p + 1)];

        memo[0][0] = true;
        memo[1][0] = false;
        bool v = true;
        for (j = 1; j <= len_p; j++) {
            v &= (p[j-1] == '*');
            memo[0][j] = v;
        }
        for (i = 0; i < len_s; i++) {
            for (j = 0; j < len_p; j++) {
                if (p[j] == '*' && (memo[(i+1) & 1][j] || memo[i & 1][j+1]))
                    memo[(i+1) & 1][j+1] = true;
                else if ((p[j] == s[i] || p[j] == '?') && memo[i & 1][j])
                    memo[(i+1) & 1][j+1] = true;
                else
                    memo[(i+1) & 1][j+1] = false;
            }
            memo[i & 1][0] = false;
        }
        bool ret = memo[i & 1][j];
        free(memo);
        free(pool);
        return ret;
    }
    

    bool match_greedy(const char *s, const char *p) {
        /* Pruning when 'p' contains more none '*' character than 's'. */
        int count_p = 0;
        for (int i = 0; p[i]; i++) {
            if (p[i] != '*') count_p++;
        }
        if (count_p > strlen(s)) return false;

        /* Match head. */
        while (*s && *p && (*p != '*')) {
            if (*s != *p && *p != '?')
                break;
            s ++;
            p ++;
        }
        // Head doesn't match.
        if (*p && *p != '*') return false;

        /* Match body. */
        while (*p == '*') {
            // Skip '*'.
            while (*p == '*') p++;
            // Ends with '*', match everything else.
            if (!*p) return true;

            int len_p;
            s = _find_first_of(s, p, len_p);
            if (!s) return false;
            p += len_p;
            if (!*p) {  /* Match tail. */
                int len_s = strlen(s);
                if (len_s < len_p) return false;
                s += (len_s - len_p);
                return _compare(s, p - len_p, len_p); 
            }
            s += len_p;
        }

        // Check if both 's' and 'p' terminates.
        return (!*s && !*p);
    }

private:
    bool _compare(const char *s, const char *p, size_t len)
    {
        for (int i = 0; i < len; i++) {
            if (!s[i] || (s[i] != p[i] && p[i] != '?'))
                return false;
        }
        return true;
    }

    const char *_find_first_of(const char *s, const char *p, int& len) {
        const char *ts, *tp;
        for (; *s; s++) {
            ts = s; tp = p;
            while (*ts && *tp && (*tp == *ts || *tp == '?')) {
                ts++; tp++;
            }
            if (!*tp || *tp == '*') {
                len = (tp - p);
                return s;
            }
        }
        return NULL;
    }
};

void test(const char *s, const char *p, bool real)
{
    Solution sol;
    bool res = sol.isMatch(s, p);
    cout << "[\033[1;" << ((res == real) ? "32mPass" : "31mFail") << "\033[0m] "
         << "isMatch(\"" << s << "\", \"" << p << "\") -> "
         << (res ? "True" : "False") << endl;
}

int main()
{
    test("aa", "a", false);
    test("aa", "aa", true);
    test("aaa", "aa", false);
    test("aa", "*", true);
    test("aa", "a*", true);
    test("ab", "?*", true);
    test("ab", "**", true);
    test("aab", "c*a*b", false);
    test("", "*a*", false);
    test("a", "*a*", true);
    test("aa", "*aa*", true);
    test("aababa", "a*b", false);
    test("aabab", "a*b", true);
    test("abcab", "abd*b", false);
    test("abc", "*ab", false);
    test("a", "*b", false);
    test("a", "?b", false);
    test("a", "*a", true);
    test("a", "?a", false);
    test("bbbaab", "a**?***", false);
    test("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*b", false);
    test("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaab", "a*b", true);
    test("aababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
         "*a*aaaa*bbabb*b*b*aaaaaaaaa*a*ba*bbb*a*ba*bb*bb*a*b*bb", false);
    test("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbabab"
         "aabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababb"
         "bbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbb"
         "aabaaababaaaabb",
         "*aa*ba*a*bb*aa*ab*a*aaaaaa*a*aaaa*bbabb*b*b*aaaaaaaaa*a*ba*bbb*a*ba*bb*bb*a*b*bb", false);
    test("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabb"
         "bbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbb"
         "bbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
         "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaa"
         "aaa*a********ba*bbb***a*ba*bb*bb**a*b*bb", false);

//    string s;
//    for (int i = 0; i < 32768; i++) s += 'a';
//    test(s.c_str(), ("*a" + s + "*").c_str());

    return 0;
}
