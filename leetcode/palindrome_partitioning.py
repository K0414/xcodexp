from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return a list of lists of string
    def partition(self, s):
        if not s: return []
        self.ispal = [[0] * len(s) for _ in range(len(s))]
        self._gen_pal(s)
        self.result = []
        self.one = []
        self._dfs(s, 0)
        return self.result

    def _dfs(self, s, start):
        if start >= len(s):
            self.result.append(self.one[:])
            return
        for i in range(start, len(s)):
            if self.ispal[start][i]:
                self.one.append(s[start:i+1])
                self._dfs(s, i+1)
                self.one.pop()

    def _gen_pal(self, s):
        for i in range(len(s)):
            self.ispal[i][i] = True
        for ln in range(1, len(s)):
            for i in range(len(s)-ln):
                self.ispal[i][i+ln] = (s[i] == s[i+ln])
                if self.ispal[i][i+ln] and i+1 <= i+ln-1:
                    self.ispal[i][i+ln] = self.ispal[i+1][i+ln-1]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.partition('1'), [['1']])
        assert_equal(s.partition('11'), [['1', '1'], ['11']])

    def test_example(self):
        s = Solution()
        assert_equal(s.partition('aab'), [ ["a","a","b"], ["aa","b"] ])
