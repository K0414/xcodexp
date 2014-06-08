from nose.tools import assert_equal

class Solution:
    # @return an integer
    def numTrees(self, n):
        catalan = [1]
        catalan.extend([0] * n)
        for i in range(1, n+1):
            for j in range(i):
                catalan[i] += catalan[j] * catalan[i-1-j]
        return catalan[n]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.numTrees(0), 1)
        assert_equal(s.numTrees(1), 1)
        assert_equal(s.numTrees(2), 2)
        assert_equal(s.numTrees(3), 5)
        assert_equal(s.numTrees(4), 14)
        assert_equal(s.numTrees(5), 42)
        assert_equal(s.numTrees(6), 132)
        assert_equal(s.numTrees(7), 429)
        assert_equal(s.numTrees(8), 1430)
        assert_equal(s.numTrees(9), 4862)
        assert_equal(s.numTrees(10), 16796)

    def test_example(self):
        pass
