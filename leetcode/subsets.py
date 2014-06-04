from nose.tools import assert_equal

class Solution:
    # @param S, a list of integer
    # @return a list of lists of integer
    def subsets(self, S):
        #return self._solve_dfs(S)
        return self._solve_loop(S)

    def _solve_loop(self, S):
        S.sort()
        results = [[]]
        for i in range(len(S)):
            for j in range(len(results)):
                results.append(results[j][:])
                results[-1].append(S[i])
        return results

    def _solve_dfs(self, S):
        S.sort()
        self.results = []
        for i in range(len(S)+1):
            self.one = []
            self._dfs(S, 0, 0, i)
        return self.results

    def _dfs(self, S, start, level, n):
        if n == level:
            self.results.append(self.one[:])
            return
        for i in range(start, len(S)):
            self.one.append(S[i])
            self._dfs(S, i+1, level+1, n)
            self.one.pop()


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.subsets([]), [[]])
        assert_equal(s.subsets([1]), [[],[1]])
        assert_equal(s.subsets([1,2]), [[],[1],[2],[1,2]])

    def test_example(self):
        s = Solution()
        r = s.subsets([1,2,3])
        r.sort()
        a = [[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
        a.sort()
        assert_equal(r, a)


if __name__=='__main__':
    s = Solution()
