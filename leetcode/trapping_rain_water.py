from nose.tools import assert_equal

class Solution:
    # @param A, a list of integers
    # @return an integer
    def trap(self, A):
        lbarrier = self._barrier(A)
        rbarrier = self._barrier(reversed(A))
        rbarrier.reverse()
        water = 0
        for i in range(len(A)):
            if lbarrier[i] > A[i] and rbarrier[i] > A[i]:
                water += (min(lbarrier[i], rbarrier[i]) - A[i])
        return water


    def _barrier(self, A):
        highest = 0
        barrier = []
        for i in A:
            barrier.append(highest)
            if i > highest:
                highest = i
        return barrier


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.trap([]), 0)
        assert_equal(s.trap([1]), 0)
        assert_equal(s.trap([1,2]), 0)
        assert_equal(s.trap([1,2,3]), 0)
        assert_equal(s.trap([1,2,1]), 0)
        assert_equal(s.trap([2,1,2]), 1)
        assert_equal(s.trap([3,2,1,0,1,2,3]), 9)

    def test_example(self):
        s = Solution()
        assert_equal(s.trap([0,1,0,2,1,0,1,3,2,1,2,1]), 6)
