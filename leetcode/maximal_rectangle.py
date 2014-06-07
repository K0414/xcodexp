from nose.tools import assert_equal

class Solution:
    # @param matrix, a list of lists of 1 length string
    # @return an integer
    def maximalRectangle(self, matrix):
        #return self._solve_scan(matrix)
        return self._solve_dp(matrix)

    def _solve_scan(self, matrix):
        if not matrix: return 0
        maxArea = 0
        row = [0] * len(matrix[0])
        for i in range(len(matrix)):
            for j in range(len(row)):
                if matrix[i][j] == '1':
                    row[j] += 1
                else:
                    row[j] = 0
            area = self._max_row_area(row)
            maxArea = max(maxArea, area)
        return maxArea

    def _max_row_area(self, row):
        stack = []
        maxArea = 0
        for i in range(len(row)):
            while stack and row[stack[-1]] > row[i]:
                tp = stack[-1]
                stack.pop()
                ln = (i - stack[-1] - 1) if stack else i
                maxArea = max(maxArea, row[tp] * ln)
            stack.append(i)
        while stack:
            tp = stack[-1]
            stack.pop()
            ln = (len(row) - stack[-1] - 1) if stack else len(row)
            maxArea = max(maxArea, row[tp] * ln)
        return maxArea

    def _solve_dp(self, matrix):
        """
        An O(n^2) DP solution from http://stackoverflow.com/questions/11481868/.

        h[i][j]  is the number of consecutive 1's above (i,j).
        l[i][j]  is how far left we can extend with bottom-right corner
                 at (i,j) and h[i][j].
        r[i][j]  is how far right we can extend with bottom-left corner
                 at (i,j) and h[i][j].
        """
        if not matrix: return 0
        m = len(matrix)
        n = len(matrix[0])
        h = [ [0] * n for _ in range(m) ]
        l = [ [0] * n for _ in range(m) ]
        r = [ [0] * n for _ in range(m) ]
        # Consecutive 1's above (i,j).
        for k in range(n):
            h[0][k] = 1 if matrix[0][k] == '1' else 0
        for i in range(1, m):
            for j in range(n):
                if matrix[i][j] == '1':
                    h[i][j] = h[i-1][j] + 1
                else:
                    h[i][j] = 0
        # Consecutive 1's with bottom-right corner at (i,j) and h[i][j].
        l[0][0] = 1 if matrix[0][0] == '1' else 0
        for k in range(1, n):
            l[0][k] = (l[0][k-1] + 1) if matrix[0][k] == '1' else 0
        for i in range(1, m):
            p = -1
            for j in range(n):
                if matrix[i][j] == '1':
                    if matrix[i-1][j] == '1':
                        l[i][j] = min(l[i-1][j], j - p)
                    else:
                        l[i][j] = j - p
                else:
                    l[i][j] = 0
                    p = j
        # Consecutive 1's with bottom-left corner at (i,j) and h[i][j].
        r[0][n-1] = 1 if matrix[0][n-1] == '1' else 0
        for k in range(n-1)[::-1]:
            r[0][k] = (r[0][k+1] + 1) if matrix[0][k] == '1' else 0
        for i in range(1, m):
            p = n
            for j in range(n)[::-1]:
                if matrix[i][j] == '1':
                    if matrix[i-1][j] == '1':
                        r[i][j] = min(r[i-1][j], p - j)
                    else:
                        r[i][j] = p - j
                else:
                    r[i][j] = 0
                    p = j
        maxArea = 0
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '1':
                    area = h[i][j] * (l[i][j] + r[i][j] - 1)
                    maxArea = max(maxArea, area)
        return maxArea


class TestSolution(object):

    def test_scan(self):
        s = Solution()
        self._simple(s._solve_scan)
        self._example(s._solve_scan)

    def test_dp(self):
        s = Solution()
        self._simple(s._solve_dp)
        self._example(s._solve_dp)

    def _simple(self, func):
        m = [['0']]
        assert_equal(func(m), 0)
        m = [['1']]
        assert_equal(func(m), 1)
        m = ['0000',
             '0110',
             '0010',
             '0000']
        assert_equal(func(m), 2)
        m = ['0100',
             '0110',
             '0100',
             '0000']
        assert_equal(func(m), 3)
        m = ['0000',
             '0110',
             '0110',
             '0000']
        assert_equal(func(m), 4)
        m = ['0100',
             '0110',
             '0110',
             '0000']
        assert_equal(func(m), 4)

    def _example(self, func):
        m = ['0010',
             '1111',
             '1111',
             '1110',
             '1100',
             '1111',
             '1110']
        assert_equal(func(m), 12)
