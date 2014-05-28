from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def minCut(self, s):
        if not s: return 0
        self.ispal = [ [False] * len(s) for i in range(len(s)) ]
        self._gen_pal(s)
        dp = [0] * len(s)
        for i in range(1, len(s)):
            dp[i] = dp[i-1]+1
            for j in range(1, i+1):
                if self.ispal[i-j][i]:
                    v = 0 if i-j<1 else dp[i-j-1]+1
                    dp[i] = min(dp[i], v)
        return dp[len(s)-1]

    def _gen_pal(self, s):
        for i in range(len(s)):
            self.ispal[i][i] = True
        for i in range(len(s)-1):
            self.ispal[i][i+1] = (s[i] == s[i+1])
        for l in range(2, len(s)):
            for i in range(len(s)-l):
                if self.ispal[i+1][i+l-1]:
                    self.ispal[i][i+l] = (s[i] == s[i+l])


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.minCut(""), 0)
        assert_equal(s.minCut("a"), 0)
        assert_equal(s.minCut("aa"), 0)
        assert_equal(s.minCut("abcbd"), 2)
        assert_equal(s.minCut("ababab"), 1)
        assert_equal(s.minCut("abababa"), 0)

    def test_example(self):
        s = Solution()
        assert_equal(s.minCut("aab"), 1)
        assert_equal(s.minCut("abcccb"), 1)
        assert_equal(s.minCut("cbbbcc"), 1)


if __name__=='__main__':
    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    sol = Solution()
    print sol.minCut(s)
