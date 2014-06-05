from nose.tools import assert_equal

class Solution:
    # @param x, a float
    # @param n, a integer
    # @return a float
    def pow(self, x, n):
        if n == 0:
            return 1

        h = n / 2
        v = pow(x, h)
        e = x if n % 2 == 1 else 1
        return v * v * e


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.pow(2,0), 1)
        assert_equal(s.pow(2,1), 2)
        assert_equal(s.pow(2,2), 4)
        assert_equal(s.pow(2,3), 8)
        assert_equal(s.pow(2,4), 16)
        assert_equal(s.pow(2,5), 32)

    def test_example(self):
        pass
