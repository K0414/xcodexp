from nose.tools import assert_equal

class Solution:
    # @param prices, a list of integer
    # @return an integer
    def maxProfit(self, prices):
        if not prices: return 0
        lowest = prices[0]
        lbound = []
        for p in prices:
            if p < lowest:
                lowest = p
            lbound.append(lowest)
        mp = 0
        for i in range(len(prices)):
            p = (prices[i] - lbound[i])
            if p > mp:
                mp = p
        return mp


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.maxProfit([]), 0)
        assert_equal(s.maxProfit([5,4,3,2,1]), 0)
        assert_equal(s.maxProfit([3,2,1,2,3,4,5,4]), 4)

    def test_example(self):
        pass
