from nose.tools import assert_equal

class Solution:
    # @param obstacleGrid, a list of lists of integers
    # @return an integer
    def uniquePathsWithObstacles(self, obstacleGrid):
        if not obstacleGrid: return 0
        m = len(obstacleGrid)
        n = len(obstacleGrid[0])
        dp = [[0] * n for i in range(m)]
        for i in range(m):
            if obstacleGrid[i][0]:
                break
            dp[i][0] = 1
        for j in range(n):
            if obstacleGrid[0][j]:
                break
            dp[0][j] = 1
        for i in range(1, m):
            for j in range(1, n):
                if obstacleGrid[i][j]:
                    dp[i][j] = 0
                else:
                    dp[i][j] = dp[i-1][j] + dp[i][j-1]
        return dp[m-1][n-1]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        p = [[0,1,0],
             [0,0,0],
             [0,0,0]]
        assert_equal(s.uniquePathsWithObstacles(p), 3)
        p = [[0,0,0],
             [0,0,0],
             [0,1,0]]
        assert_equal(s.uniquePathsWithObstacles(p), 3)
        p = [[0,0,0],
             [0,0,0],
             [0,0,0]]
        assert_equal(s.uniquePathsWithObstacles(p), 6)

    def test_example(self):
        s = Solution()
        p = [[0,0,0],
             [0,1,0],
             [0,0,0]]
        assert_equal(s.uniquePathsWithObstacles(p), 2)
