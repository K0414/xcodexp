from nose.tools import assert_equal

class Solution:
    # @return a boolean
    def isMatch(self, s, p):
        return self._solve_backtrace(s, p)

    def _solve_backtrace(self, s, p):
        while s and p and p[-1] != '*':
            if (p[-1] != s[-1] and p[-1] != '.'):
                return False
            p = p[:-1]
            s = s[:-1]
        return self._matchhere(s, p)

    def _matchhere(self, s, p):
        if not s and not p: return True
        if not p: return False
        if len(p) > 1 and p[1] == '*':
            return self._matchstar(p[0], s, p[2:])
        if s and (p[0] == s[0] or p[0] == '.'):
            return self._matchhere(s[1:], p[1:])
        return False

    def _matchstar(self, c, s, p):
        i = 0
        while i < len(s) and (c == s[i] or c == '.'):
            i += 1
            if self._matchhere(s[i:], p):
                return True
        return self._matchhere(s, p)


class TestSolution(object):

    def test_backtrace(self):
        s = Solution()
        self._simple(s._solve_backtrace)
        self._example(s._solve_backtrace)

    def test_nfa(self):
        s = Solution()

    def _simple(self, func):
        assert_equal(func("", ""), True)
        assert_equal(func("a", "a"), True)
        assert_equal(func("a", "b"), False)
        assert_equal(func("aab", "a*b"), True)
        assert_equal(func("aaab", "a*b"), True)
        assert_equal(func("aaaababac", "a*b*a*b*a*c"), True)
        assert_equal(func("aaaababac", "a*d*b*a*b*a*c"), True)
        assert_equal(func("aaaababac", ".*c"), True)
        assert_equal(func("aaaababac", "a*.*c"), True)
        assert_equal(func("aaaababac", "a*db*a*b*a*c"), False)
        assert_equal(func("aaaababac", ".*"), True)
        assert_equal(func("abcdef", "abc"), False)
        assert_equal(func("abc", "abcdef"), False)

    def _example(self, func):
        assert_equal(func("aa", "a"), False)
        assert_equal(func("aa", "aa"), True)
        assert_equal(func("aaa", "aa"), False)
        assert_equal(func("aa", "a*"), True)
        assert_equal(func("aa", ".*"), True)
        assert_equal(func("ab", ".*"), True)
        assert_equal(func("aab", "c*a*b"), True)
        assert_equal(func("ab", ".*b"), True)
        assert_equal(func("ab", ".*c"), False)
        assert_equal(func("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c"), False)

