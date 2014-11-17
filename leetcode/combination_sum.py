from nose.tools import assert_equal

class Solution:
    # @param candidates, a list of integers
    # @param target, integer
    # @return a list of lists of integers
    def combinationSum(self, candidates, target):
        results = list()
        curr = list()
        self._dfs(sorted(candidates), target, 0, results, curr)
        return results

    def _dfs(self, candidates, target, start, results, curr):
        for i in range(start, len(candidates)):
            c = candidates[i]
            if c == target:
                curr.append(c)
                results.append([x for x in curr])
                curr.pop()
                return
            elif c < target:
                target -= c
                curr.append(c)
                self._dfs(candidates, target, i, results, curr)
                curr.pop()
                target += c
            else:
                break


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(sorted(s.combinationSum([], 7)), sorted([]))
        assert_equal(sorted(s.combinationSum([1], 7)), sorted([[1,1,1,1,1,1,1]]))

    def test_example(self):
        s = Solution()
        assert_equal(sorted(s.combinationSum([2,3,6,7], 7)), sorted([[7], [2,2,3]]))
