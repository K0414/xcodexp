from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @param dict, a set of string
    # @return a boolean
    def wordBreak(self, s, dict):
        return self._solve_dp(s, dict)
        alphabet = list(''.join(dict))
        for c in s:
            if c not in alphabet:
                return False
        return self._solve(s, dict)

    def _solve(self, s, dict):
        if not s:
            return True

        for w in dict:
            if len(w) <= len(s):
                if s[:len(w)] == w:
                    if self._solve(s[len(w):], dict):
                        return True
        return False

    def _solve_dp(self, s, dict):
        """
        A DP solution from https://oj.leetcode.com/discuss/1523.
        """
        dp = [False] * (len(s) + 1)
        dp[0] = True
        for i in range(1, len(s)+1):
            for j in range(i):
                if dp[j] and (s[j:i] in dict):
                    dp[i] = True
                    break
        return dp[len(s)]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.wordBreak('leetcode', set(['lee', 'code'])), False)
        assert_equal(s.wordBreak('leetcode', set(['leetc', 'code'])), False)
        assert_equal(s.wordBreak('leetcode', set(['leetc', 'leet', 'code'])), True)

    def test_example(self):
        s = Solution()
        assert_equal(s.wordBreak('leetcode', set(['leet', 'code'])), True)
        assert_equal(s.wordBreak('bb', set(["a","b","bbb","bbbb"])), True)
        assert_equal(s.wordBreak('aaaaaaa', set(["aaaa","aaa"])), True)
        assert_equal(s.wordBreak('aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab', set(["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"])), False)
