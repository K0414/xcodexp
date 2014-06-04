from nose.tools import assert_equal

class Solution:
    # @return a list of lists of string
    def solveNQueens(self, n):
        if n <= 0: return []
        self.results = []
        self.board = [['.'] * n for _ in range(n)]
        self._solve(n, 0)
        return self.results

    def _solve(self, n, row):
        if row == n:
            res = [''.join(x) for x in self.board]
            self.results.append(res)
            return

        for j in range(n):
            if self._check(n, row, j):
                self.board[row][j] = 'Q'
                self._solve(n, row+1)
                self.board[row][j] = '.'

    def _check(self, n, row, j):
        for k in range(row+1):
            if self.board[k][j] == 'Q':
                return False
            if row-k >= 0 and j-k >= 0 and self.board[row-k][j-k] == 'Q':
                return False
            if row-k >= 0 and j+k < n and self.board[row-k][j+k] == 'Q':
                return False
        return True



class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.solveNQueens(0), [])
        assert_equal(s.solveNQueens(1), [['Q']])
        assert_equal(s.solveNQueens(2), [])
        assert_equal(s.solveNQueens(3), [])

    def test_example(self):
        s = Solution()
        r = [[".Q..", "...Q", "Q...", "..Q."],
             ["..Q.", "Q...", "...Q", ".Q.."]]
        assert_equal(s.solveNQueens(4), r)


if __name__=='__main__':
    s = Solution()
    print s.solveNQueens(9)
