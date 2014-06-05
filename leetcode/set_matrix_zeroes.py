from nose.tools import assert_equal

class Solution:
    # @param matrix, a list of lists of integers
    # RETURN NOTHING, MODIFY matrix IN PLACE.
    def setZeroes(self, matrix):
        """
        Project zeroes on the first row and column.
        """
        if not matrix: return
        m = len(matrix)
        n = len(matrix[0])
        firstRowHasZero = False
        firstColHasZero = False
        for k in range(n):
            if matrix[0][k] == 0:
                firstRowHasZero = True
        for k in range(m):
            if matrix[k][0] == 0:
                firstColHasZero = True
        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][j] == 0:
                    matrix[0][j] = 0
                    matrix[i][0] = 0
        for i in range(1, m):
            for j in range(1, n):
                if matrix[0][j] == 0 or matrix[i][0] == 0:
                    matrix[i][j] = 0
        if firstRowHasZero:
            for k in range(n):
                matrix[0][k] = 0
        if firstColHasZero:
            for k in range(m):
                matrix[k][0] = 0


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        m = [[1, 0]]
        r = [[0, 0]]
        s.setZeroes(m)
        assert_equal(m, r)
        m = [[1, 1],
             [1, 0]]
        r = [[1, 0],
             [0, 0]]
        s.setZeroes(m)
        assert_equal(m, r)
        m = [[1, 1, 1, 1, 1],
             [1, 0, 1, 0, 1],
             [1, 1, 0, 1, 1],
             [1, 1, 1, 1, 1]]
        r = [[1, 0, 0, 0, 1],
             [0, 0, 0, 0, 0],
             [0, 0, 0, 0, 0],
             [1, 0, 0, 0, 1]]
        s.setZeroes(m)
        assert_equal(m, r)

    def test_example(self):
        s = Solution()
