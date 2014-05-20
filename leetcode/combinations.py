from nose.tools import assert_equal

class Solution:
    # @return a list of lists of integers
    def combine(self, n, k):
        result = []
        one = []
        self._solve(1, n, k, one, result)
        return result

    def _solve(self, s, n, k, one, result):
        if k == 0:
            result.append(one[:])
            return

        # set s always '1' for permutations.
        for i in range(s, n+1):
            if i in one: continue
            one.append(i)
            self._solve(i+1, n, k-1, one, result)
            one.pop()

class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.combine(1, 1), [[1]])
        assert_equal(s.combine(2, 1), [[1], [2]])
        assert_equal(s.combine(2, 2), [[1, 2]])
        assert_equal(s.combine(3, 3), [[1, 2, 3]])
        assert_equal(s.combine(4, 2), [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]])
