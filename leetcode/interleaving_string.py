from nose.tools import assert_equal

class Solution:
    # @return a boolean
    def isInterleave(self, s1, s2, s3):
        #return self._check_recursive_tle(s1, s2, s3)
        return self._check_dp(s1, s2, s3)

    def _check_dp(self, s1, s2, s3):
        m = len(s1)
        n = len(s2)
        if m+n != len(s3):
            return False
        dp = [[False] * (n+1) for _ in range(m+1)]
        dp[0][0] = True
        for i in range(1, m+1):
            if (s1[i-1] == s3[i-1]):
                dp[i][0] = True
            else:
                break
        for j in range(1, n+1):
            if (s2[j-1] == s3[j-1]):
                dp[0][j] = True
            else:
                break
        for i in range(1, m+1):
            for j in range(1, n+1):
                dp[i][j] = (dp[i-1][j] and s1[i-1] == s3[i+j-1]) \
                           or (dp[i][j-1] and s2[j-1] == s3[i+j-1])
        return dp[m][n]

    def _check_recursive_tle(self, s1, s2, s3):
        if not s1: return (s2 == s3)
        if not s2: return (s1 == s3)

        if len(s1) + len(s2) != len(s3):
            return False
        tab = [0] * 26
        for c in s1:
            tab[ord(c) - ord('a')] += 1
        for c in s2:
            tab[ord(c) - ord('a')] += 1
        for c in s3:
            tab[ord(c) - ord('a')] -= 1
        for i in range(26):
            if tab[i] != 0:
                return False
        if s1[0] == s2[0]:
            if s1[0] != s3[0]:
                return False
            if self._check_recursive_tle(s1[1:], s2, s3[1:]):
                return True
            elif self._check_recursive_tle(s1, s2[1:], s3[1:]):
                return True
            return False
        elif s1[0] == s3[0]:
            return self._check_recursive_tle(s1[1:], s2, s3[1:])
        elif s2[0] == s3[0]:
            return self._check_recursive_tle(s1, s2[1:], s3[1:])
        else:
            return False


class TestSolution(object):

    def test_simple(self):
        pass

    def test_example(self):
        s = Solution()
        assert_equal(s.isInterleave("aabcc", "dbbca", "aadbbcbcac"), True)
        assert_equal(s.isInterleave("aabcc", "dbbca", "aadbbbaccc"), False)
        assert_equal(s.isInterleave("a", "b", "a"), False)
        assert_equal(s.isInterleave("aacaac", "aacaaeaac", "aacaaeaaeaacaac"), False)
