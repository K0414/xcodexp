from nose.tools import assert_equal

class Solution:
    # @param prices, a list of integer
    # @return an integer
    def maxProfit(self, prices):
        #return self._max_nn(prices)
        #return self._max_n(prices)
        return self._max2(prices)
        return self._max_general(prices)

    def _max_nn(self, prices):
        if len(prices) < 4: return self._max1(prices)[2]
        mp = 0
        for i in range(2, len(prices)-1):
            mh = self._max1(prices[:i])[2]
            mt = self._max1(prices[i:])[2]
            m = 0
            if mh > 0: m += mh
            if mt > 0: m += mt
            mp = max(m, mp)
        return mp

    def _max_n(self, prices):
        l, r, mp = self._max1(prices)
        if not mp: return 0
        # 1) outside.
        mp1 = max(self._max1(prices[:l])[2], self._max1(prices[r+1:])[2])
        # 2) inside.
        mp2 = self._max1(prices[l:r+1][::-1])[2]
        return mp + max(mp1, mp2)

    def _max1(self, prices):
        if not prices: return -1, -1, 0
        l = 0
        lbound = []
        for i in range(len(prices)):
            if prices[i] < prices[l]:
                l = i
            lbound.append(l)
        mp = 0
        l = -1
        r = -1
        for i in range(len(prices)):
            p = (prices[i] - prices[lbound[i]])
            if p > mp:
                mp = p
                l = lbound[i]
                r = i
        return l, r, mp

    def _max2(self, prices):
        if not prices: return 0
        forward = [0] * len(prices)
        backward = [0] * len(prices)
        maxp = 0
        valley = prices[0]
        for i in range(len(prices)):
            valley = min(valley, prices[i])
            if i > 0:
                forward[i] = max(forward[i-1], (prices[i] - valley))
            maxp = max(maxp, forward[i])
        peak = 0
        for i in range(len(prices))[::-1]:
            peak = max(peak, prices[i])
            if i < len(prices)-1:
                backward[i] = max(backward[i+1], (peak - prices[i]))
                maxp = max(maxp, backward[i+1]+forward[i])
        return maxp

    def _max_miklos_csuros(self, prices):
        # Refer to:
        # https://oj.leetcode.com/discuss/1381/any-solutions-better-than-o-n-2?show=2703#a2703
        # http://www.iro.umontreal.ca/~csuros/papers/mle-segmentation-full.pdf
        pass


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.maxProfit([]), 0)
        assert_equal(s.maxProfit([1,2]), 1)
        assert_equal(s.maxProfit([3,2,6,5,0,3]), 7)
        assert_equal(s.maxProfit([5,4,3,2,1]), 0)
        assert_equal(s.maxProfit([3,2,1,2,3,4,5,4]), 4)
        assert_equal(s.maxProfit([3,2,1,2,3,1,5,2,8]), 10)

    def test_example(self):
        pass
