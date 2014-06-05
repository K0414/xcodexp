from nose.tools import assert_equal

class Solution:
    # @param num, a list of integer
    # @return a list of lists of integers
    def permuteUnique(self, num):
        if not num: return []
        self.one = []
        self.result = []
        self.used = [False] * len(num)
        num.sort()
        self._perm(num)
        return self.result

    def _perm(self, num):
        if len(self.one) == len(num):
            self.result.append(self.one[:])
            return

        i = 0
        while i < len(num):
            if not self.used[i]:
                self.used[i] = True
                self.one.append(num[i])
                self._perm(num)
                self.one.pop()
                self.used[i] = False
                while i < len(num)-1 and num[i] == num[i+1]:
                    i += 1
            i += 1


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.permuteUnique([]), [])
        assert_equal(s.permuteUnique([1]), [[1]])
        assert_equal(s.permuteUnique([1,1]), [[1,1]])

    def test_example(self):
        s = Solution()
        assert_equal(s.permuteUnique([1,1,2]), [[1,1,2],[1,2,1],[2,1,1]])
