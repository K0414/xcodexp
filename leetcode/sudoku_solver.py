from nose.tools import assert_equal

class Solution:
    # @param board, a 9x9 2D array
    # Solve the Sudoku by modifying the input board in-place.
    # Do not return any value.
    def solveSudoku(self, board):
        c = 0
        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    c += 1
        self._solve(board, c)

    def _solve(self, board, c):
        if c == 0:
            return True
        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    for k in range(1, 10):
                        if self._check(board, i, j, str(k)):
                            s = [x for x in board[i]]
                            s[j] = str(k)
                            board[i] = ''.join(s)
                            if self._solve(board, c-1):
                                return True
                            s[j] = '.'
                            board[i] = ''.join(s)
                    return False

    def _check(self, board, i, j, v):
        for k in range(9):
            if board[i][k] == v or board[k][j] == v:
                return False
        r = i - i % 3
        c = j - j % 3
        for x in range(r, r+3):
            for y in range(c, c+3):
                if board[x][y] == v:
                    return False
        return True


class TestSolution(object):

    def test_simple(self):
        pass

    def test_example(self):
        s = Solution()
        b = ['53..7....',
             '6..195...',
             '.98....6.',
             '8...6...3',
             '4..8.3..1',
             '7...2...6',
             '.6....28.',
             '...419..5',
             '....8..79']
        r = ['534678912',
             '672195348',
             '198342567',
             '859761423',
             '426853791',
             '713924856',
             '961537284',
             '287419635',
             '345286179']
        s.solveSudoku(b)
        assert_equal(b, r)

if __name__=='__main__':
    ts = TestSolution()
    ts.test_example()
