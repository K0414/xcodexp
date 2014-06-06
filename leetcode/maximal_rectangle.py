from nose.tools import assert_equal

class Solution:
    # @param matrix, a list of lists of 1 length string
    # @return an integer
    def maximalRectangle(self, matrix):
        return self._solve_scan(matrix)

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

#    def _solve_dp(self, matrix):
#        if not matrix: return 0
#        m = len(matrix)
#        n = len(matrix[0])
#        dp = [ [0] * n for _ in range(m) ]
#        dp[0][0] = 1 if matrix[0][0] == '1' else 0
#        maxArea = dp[0][0]
#        for i in range(1, m):
#            if dp[i-1][0] and matrix[i][0] == '1':
#                dp[i][0] = dp[i-1][0] + 1
#            else:
#                dp[i][0] = 0
#        for j in range(1, n):
#            if dp[0][j-1] and matrix[0][j] == '1':
#                dp[0][j] = dp[0][j-1] + 1
#            else:
#                dp[0][j] = 0
#        for i in range(1, m):
#            for j in range(1, n):
#                area1 = ...
#                area2 = ...
#                dp[i][j] = max(area1, area2)
#                maxArea = max(maxArea, dp[i][j])
#        return maxArea


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        m = [['0']]
        assert_equal(s.maximalRectangle(m), 0)
        m = [['1']]
        assert_equal(s.maximalRectangle(m), 1)
        m = [['0','0','0','0'],
             ['0','1','1','0'],
             ['0','0','1','0'],
             ['0','0','0','0']]
        assert_equal(s.maximalRectangle(m), 2)
        m = [['0','1','0','0'],
             ['0','1','1','0'],
             ['0','1','0','0'],
             ['0','0','0','0']]
        assert_equal(s.maximalRectangle(m), 3)
        m = [['0','0','0','0'],
             ['0','1','1','0'],
             ['0','1','1','0'],
             ['0','0','0','0']]
        assert_equal(s.maximalRectangle(m), 4)
        m = [['0','1','0','0'],
             ['0','1','1','0'],
             ['0','1','1','0'],
             ['0','0','0','0']]
        assert_equal(s.maximalRectangle(m), 4)

    def test_example(self):
        pass
