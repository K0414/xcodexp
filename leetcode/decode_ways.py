from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def numDecodings(self, s):
        if not s or s[0] == '0': return 0
        if len(s) < 2: return 1
        memo = [1, 0, 0]
        if s[1] == '0':
            if s[0] == '1' or s[0] == '2':
                memo[1] = 1
        else:
            if s[0] == '1':
                memo[1] = 2
            elif s[0] == '2' and s[1] <= '6':
                memo[1] = 2
            else:
                memo[1] = 1
        for i in range(2, len(s)):
            if s[i] == '0':
                if (s[i-1] == '0' or s[i-1] > '2'):
                    return 0
                else:
                    memo[i % 3] = memo[(i-2) % 3]
                    continue
            memo[i % 3] = memo[(i-1) % 3]
            if (s[i-1] == '1') or (s[i-1] == '2' and s[i] <= '6'):
                memo[i % 3] += memo[(i - 2) % 3]
        return memo[(len(s) - 1) % 3]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.numDecodings("1234"), 3)
        assert_equal(s.numDecodings("10"), 1)
        assert_equal(s.numDecodings("101"), 1)
        assert_equal(s.numDecodings("20"), 1)
        assert_equal(s.numDecodings("201"), 1)
        assert_equal(s.numDecodings("30"), 0)
        assert_equal(s.numDecodings("301"), 0)
        assert_equal(s.numDecodings("11"), 2)
        assert_equal(s.numDecodings("111"), 3)

    def test_example(self):
        s = Solution()
        assert_equal(s.numDecodings("12"), 2)
        assert_equal(s.numDecodings("0"), 0)
        assert_equal(s.numDecodings("27"), 1)
