from nose.tools import assert_equal

class Solution:
    # @param prices, a list of integer
    # @return an integer
    def maxProfit(self, prices):
        maxp = 0
        for i in range(1, len(prices)):
            if (prices[i] - prices[i-1]) > 0:
                maxp += (prices[i] - prices[i-1])
        return maxp


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.maxProfit([]), 0)
        assert_equal(s.maxProfit([5,4,3,2,1]), 0)
        assert_equal(s.maxProfit([3,2,1,2,3,4,5,4]), 4)

    def test_example(self):
        pass
