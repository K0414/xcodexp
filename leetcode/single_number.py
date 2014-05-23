from nose.tools import assert_equal

class Solution:
    # @param A, a list of integer
    # @return an integer
    def singleNumber(self, A):
        x = 0
        for d in A:
            x ^= d
        return x


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.singleNumber([101]), 101)
        assert_equal(s.singleNumber([2,3,4,5,4,3,2]), 5)

    def test_example(self):
        pass
