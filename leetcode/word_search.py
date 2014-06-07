from nose.tools import assert_equal

class Solution:
    # @param board, a list of lists of 1 length string
    # @param word, a string
    # @return a boolean
    def exist(self, board, word):
        if not board: return False
        m = len(board)
        n = len(board[0])
        self.used = [ [0] * n for _ in range(m) ]
        for i in range(m):
            for j in range(n):
                if self._solve_dfs(board, word, i, j, 0):
                    return True
        return False

    def _solve_dfs(self, board, word, i, j, k):
        if len(word) == 1:
            return board[i][j] == word[k]
        if k == len(word):
            return True
        if board[i][j] != word[k] or self.used[i][j]:
            return False
        m = len(board)
        n = len(board[0])
        self.used[i][j] = 1
        if i > 0: # Up.
            if self._solve_dfs(board, word, i-1, j, k+1):
                return True
        if j < n-1: # Right.
            if self._solve_dfs(board, word, i, j+1, k+1):
                return True
        if i < m-1: # Down.
            if self._solve_dfs(board, word, i+1, j, k+1):
                return True
        if j > 0: # Left.
            if self._solve_dfs(board, word, i, j-1, k+1):
                return True
        self.used[i][j] = 0
        return False


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        b = []
        assert_equal(s.exist(b, "A"), False)
        b = ['A']
        assert_equal(s.exist(b, "A"), True)
        b = ['A']
        assert_equal(s.exist(b, "B"), False)
        b = ['A']
        assert_equal(s.exist(b, "AA"), False)

    def test_example(self):
        s = Solution()
        b = ["ABCE",
             "SFCS",
             "ADEE"]
        assert_equal(s.exist(b, "ABCCED"), True)
        assert_equal(s.exist(b, "SEE"), True)
        assert_equal(s.exist(b, "ABCB"), False)
