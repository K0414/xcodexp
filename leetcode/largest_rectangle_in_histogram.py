from nose.tools import assert_equal

class Solution:
    # @param height, a list of integer
    # @return an integer
    def largestRectangleArea(self, height):
        #return _solve_naive(self, height)
        return _solve_dc_segtree(self, height)
        return _solve_stack(self, height)

    def _solve_stack(self, height):
        pass

    def _solve_dc_segtree(self, height):
        pass

    def _solve_naive(self, height):
        maxArea = 0
        for i in range(len(height)):
            for j in range(i, len(height)):
                m = height[i]
                for k in range(i, j+1):
                    m = min(m, height[k])
                maxArea = max(maxArea, m * (j-i+1))
        return maxArea


class TestSolution(object):

    def test_simple(self):
        s = Solution()

    def test_example(self):
        s = Solution()
        assert_equal(s.largestRectangleArea([2,1,5,6,2,3]), 10)
