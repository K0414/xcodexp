"""Key observation: Reduce complexity from O(n^k) to O(n^(k-1)) by recursively reducing K-Sum to 2-Sum and solve it in O(nlogn)."""

from nose.tools import assert_equal

class Solution:
    # @return a list of lists of length 4, [[val1,val2,val3,val4]]
    def fourSum(self, num, target):
        self.result = []
        self.one = []
        num.sort()
        if sum(num[-4:]) < target or sum(num[:4]) > target:
            return []
        self._sum(num, target, 0, 4)
        return self.result

    def _sum(self, num, target, start, level):
        if level == 2:
            l = start
            r = len(num)-1
            while l < r:
                if num[l] + num[r] == target:
                    v = self.one + [num[l], num[r]]
                    if v not in self.result:
                        self.result.append(v)
                    l += 1
                    r -= 1
                elif num[l] + num[r] < target:
                    l += 1
                else:
                    r -= 1
            return

        for i in range(start, len(num)):
            self.one.append(num[i])
            self._sum(num, target-num[i], i+1, level-1)
            self.one.pop()


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.fourSum([], 0), [])
        assert_equal(s.fourSum([1], 0), [])
        assert_equal(s.fourSum([1,2], 0), [])
        assert_equal(s.fourSum([1,2,3,4], 10), [[1,2,3,4]])
        assert_equal(s.fourSum([1,2,3,4,5], 10), [[1,2,3,4]])

    def test_example(self):
        s = Solution()
        r = [[-1,  0, 0, 1], [-2, -1, 1, 2], [-2,  0, 0, 2]]
        r.sort()
        assert_equal(s.fourSum([1,0,-1,0,-2,2], 0), r)
        r = [[-5,-4,-3,1]]
        r.sort()
        assert_equal(s.fourSum([1,-2,-5,-4,-3,3,3,5], -11), r)
