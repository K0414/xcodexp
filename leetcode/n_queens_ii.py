from nose.tools import assert_equal

class Solution:
    # @return a list of lists of string
    def solveNQueens(self, n):
        #return self._solve_dfs(n)
        return self._solve_bits(n)

    def _solve_bits(self, n):
        if n <= 0: return 0
        self.results = 0
        self.limit = (1 << n) - 1
        self._bits(0, 0, 0)
        return self.results

    def _bits(self, h, l, r):
        """
        backtrace program using bit-wise operation to speed up calculation.
        'limit' is all '1's.
        'h'     is the bits all the queens vertically projected on a row.
                If h==limit, then it's done, answer++.
        'r'     is the bits all the queens anti-diagonally projected on a row.
        'l'     is the bits all the queens diagonally projected on a row.
        """
        if h == self.limit:
            self.results += 1
            return
        pos = self.limit & (~(h|l|r))
        while pos:
            p = pos & (-pos)
            pos -= p
            self._bits(h+p, (l+p)<<1, (r+p)>>1)

    def _solve_dfs(self, n):
        if n <= 0: return 0
        self.results = 0
        self.board = [['.'] * n for _ in range(n)]
        self._dfs(n, 0)
        return self.results

    def _dfs(self, n, row):
        if row == n:
            self.results += 1
            return

        for j in range(n):
            if self._check(n, row, j):
                self.board[row][j] = 'Q'
                self._dfs(n, row+1)
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
        assert_equal(s.solveNQueens(0), 0)
        assert_equal(s.solveNQueens(1), 1)
        assert_equal(s.solveNQueens(2), 0)
        assert_equal(s.solveNQueens(3), 0)
        assert_equal(s.solveNQueens(8), 92)

    def test_example(self):
        s = Solution()
        assert_equal(s.solveNQueens(4), 2)


if __name__=='__main__':
    s = Solution()
    print s.solveNQueens(9)
