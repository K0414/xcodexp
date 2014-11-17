#encoding: utf-8

from nose.tools import assert_equal
"""
二分查找某个值时，while条件包含等于，更新l/r时为mid+/-1
二分查找最小值时，while条件不含等于，更新l/r时为mid
"""

class Solution:
    # @param num, a list of integer
    # @return an integer
    def findMin(self, num):
        return self._binsearch(num)

    def _binsearch(self, num):
        start = 0
        end = len(num)-1
        while start < end:
            mid = start + (end - start) / 2
            if num[end] > num[mid]:
                if num[start] >= num[mid]:
                    end = mid
                else:
                    return num[start]
            elif num[end] < num[mid]:
                start = mid + 1
            else:
                if num[start] == num[end]:
                    start += 1
                    end -= 1
                else:
                    end = mid
        return num[start]


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.findMin([3,3,4]), 3)
        assert_equal(s.findMin([3,3,3,3,3,3,3]), 3)
        assert_equal(s.findMin([5,6,6,6,6,3,4,4,4]), 3)
        assert_equal(s.findMin([6,6,6,6,3,6,6]), 3)

    def test_example(self):
        s = Solution()
        assert_equal(s.findMin([4,5,6,7,0,1,2]), 0)
