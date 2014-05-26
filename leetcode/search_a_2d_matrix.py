from nose.tools import assert_equal

class Solution:
    # @param matrix, a list of lists of integers
    # @param target, an integer
    # @return a boolean
    def searchMatrix(self, matrix, target):
        if not matrix: return False
        i = 0
        while i < len(matrix) and matrix[i][0] <= target:
            i += 1
        i -= 1
        if i < 0 or i == len(matrix):
            return False
        for n in matrix[i]:
            if n == target:
                return True
        return False


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        m = []
        assert_equal(s.searchMatrix(m, 3), False)
        m = [[1]]
        assert_equal(s.searchMatrix(m, 1), True)
        m = [[1]]
        assert_equal(s.searchMatrix(m, 3), False)
        m = [[1]]
        assert_equal(s.searchMatrix(m, 0), False)

    def test_example(self):
        s = Solution()
        m = [ [1,   3,  5,  7],
              [10, 11, 16, 20],
              [23, 30, 34, 50] ]
        assert_equal(s.searchMatrix(m, 3), True)
        assert_equal(s.searchMatrix(m, 10), True)
        assert_equal(s.searchMatrix(m, 0), False)
        assert_equal(s.searchMatrix(m, 11), True)
        assert_equal(s.searchMatrix(m, 15), False)
        assert_equal(s.searchMatrix(m, 30), True)
        assert_equal(s.searchMatrix(m, 32), False)
        assert_equal(s.searchMatrix(m, 50), True)
        assert_equal(s.searchMatrix(m, 60), False)
