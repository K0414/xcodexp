from nose.tools import assert_equal

class Solution:
    # @param grid, a list of lists of integers
    # @return an integer
    def minPathSum(self, grid):
        if not grid: return 0
        m = len(grid)
        n = len(grid[0])
        dp = [[0] * n for _ in range(m)]
        dp[0][0] = grid[0][0]
        for i in range(1, m):
            dp[i][0] = dp[i-1][0] + grid[i][0]
        for j in range(1, n):
            dp[0][j] = dp[0][j-1] + grid[0][j]
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        return dp[m-1][n-1]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        g = [[1]]
        assert_equal(s.minPathSum(g), 1)
        g = [[1,2,3]]
        assert_equal(s.minPathSum(g), 6)
        g = [[1],
             [2],
             [3]]
        assert_equal(s.minPathSum(g), 6)
        g = [[1,2,3],
             [4,5,6],
             [7,8,9]]
        assert_equal(s.minPathSum(g), 21)

    def test_example(self):
        pass
