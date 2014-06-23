from nose.tools import assert_equal

class Solution:
    # @param board, a 2D array
    # Capture all regions by modifying the input board in-place.
    # Do not return any value.
    def solve(self, board):
        if not board: return
        m = len(board)
        n = len(board[0])
        for i in range(1, m-1):
            for j in range(1, n-1):
                if board[i][j] == 'O':
                    self._fill_bfs(board, i, j)
        for i in range(m):
            for j in range(n):
                if board[i][j] == 'V':
                    board[i][j] = 'O'

    def _fill_bfs(self, board, row, col):
        m = len(board)
        n = len(board[0])
        p = []
        q = [(row, col)]
        char = 'X'
        while q:
            i, j = q.pop(0)
            p.append((i, j))
            if board[i-1][j] == 'O':
                if i-1 > 0:
                    board[i-1][j] = 'V'
                    q.append((i-1, j))
                else:
                    char = 'V'
            if board[i][j+1] == 'O':
                if j+1 < n-1:
                    board[i][j+1] = 'V'
                    q.append((i, j+1))
                else:
                    char = 'V'
            if board[i+1][j] == 'O':
                if i+1 < m-1:
                    board[i+1][j] = 'V'
                    q.append((i+1, j))
                else:
                    char = 'V'
            if board[i][j-1] == 'O':
                if j-1 > 0:
                    board[i][j-1] = 'V'
                    q.append((i, j-1))
                else:
                    char = 'V'
        for i, j in p:
            board[i][j] = char


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        b = [list('O')]
        r = [list('O')]
        s.solve(b)
        assert_equal(b, r)
        b = [list('X')]
        r = [list('X')]
        s.solve(b)
        assert_equal(b, r)

    def test_example(self):
        s = Solution()
        b = [list('XXXX'),
             list('XOOX'),
             list('XXOX'),
             list('XOXX')]
        r = [list('XXXX'),
             list('XXXX'),
             list('XXXX'),
             list('XOXX')]
        s.solve(b)
        assert_equal(b, r)
        b = [list('OOOOXX'),
             list('OOOOOO'),
             list('OXOXOO'),
             list('OXOOXO'),
             list('OXOXOO'),
             list('OXOOOO')]
        r = [list('OOOOXX'),
             list('OOOOOO'),
             list('OXOXOO'),
             list('OXOOXO'),
             list('OXOXOO'),
             list('OXOOOO')]
        s.solve(b)
        assert_equal(b, r)
        b = [list('XOXOOOO'),
             list('XOOOOOO'),
             list('XOOOOXO'),
             list('OOOOXOX'),
             list('OXOOOOO'),
             list('OOOOOOO'),
             list('OXOOOOO')]
        r = [list('XOXOOOO'),
             list('XOOOOOO'),
             list('XOOOOXO'),
             list('OOOOXOX'),
             list('OXOOOOO'),
             list('OOOOOOO'),
             list('OXOOOOO')]
        s.solve(b)
        assert_equal(b, r)
