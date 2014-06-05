from nose.tools import assert_equal

class Solution:
    # @param prices, a list of integer
    # @return an integer
    def maxProfit(self, prices):
        #return self._max_2n(prices)
        return self._max_dp(prices)

    def _max_2n(self, prices):
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

    def _max_dp(self, prices):
        maxp = 0
        dp = 0
        for i in range(1, len(prices)):
            if dp > 0:
                dp += (prices[i] - prices[i-1])
            else:
                dp = max(0, (prices[i] - prices[i-1]))
            maxp = max(dp, maxp)
        return maxp


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.maxProfit([]), 0)
        assert_equal(s.maxProfit([5,4,3,2,1]), 0)
        assert_equal(s.maxProfit([3,2,1,2,3,4,5,4]), 4)

    def test_example(self):
        pass
