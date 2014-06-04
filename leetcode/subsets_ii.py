from nose.tools import assert_equal

class Solution:
    # @param num, a list of integer
    # @return a list of lists of integer
    def subsetsWithDup(self, S):
        #return self._solve_dfs(S)
        return self._solve_loop(S)

    def _solve_loop(self, S):
        S.sort()
        results = [[]]
        count = 1
        for i in range(len(S)):
            if i > 0 and S[i] != S[i-1]:
                count = len(results)
            # If previous and current elements are the same, we should only
            # use the sub-sets containing the predecessor.
            for j in range(len(results)-count, len(results)):
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
            if self.one not in self.results:
                self.results.append(self.one[:])
            return
        for i in range(start, len(S)):
            self.one.append(S[i])
            self._dfs(S, i+1, level+1, n)
            self.one.pop()


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.subsetsWithDup([]), [[]])
        assert_equal(s.subsetsWithDup([1]), [[],[1]])
        assert_equal(s.subsetsWithDup([1,2]), [[],[1],[2],[1,2]])

    def test_example(self):
        s = Solution()
        assert_equal(s.subsetsWithDup([1,2,2]), [[],[1],[2],[1,2],[2,2],[1,2,2]])
        assert_equal(s.subsetsWithDup([5,5,5,5,5]), [[],[5],[5,5],[5,5,5],[5,5,5,5],[5,5,5,5,5]])


if __name__=='__main__':
    s = Solution()
