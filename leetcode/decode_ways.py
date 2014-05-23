from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def numDecodings(self, s):
#        endOne = 1
#        endTwo = 0
#        for i in range(1, len(s)):
#            oldTwo = endTwo
#            if (s[i-1] < '2') or (s[i-1] == '2' and s[i] <= '6'):
#                endTwo = endOne + 1
#                endOne += 1
#            else:
#                endTwo = 0
#            endOne += oldTwo
#        return (endOne + endTwo)


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.numDecodings("1234"), 3)

    def test_example(self):
        s = Solution()
        assert_equal(s.numDecodings("12"), 2)
