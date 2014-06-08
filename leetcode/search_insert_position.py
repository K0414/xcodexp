from nose.tools import assert_equal

class Solution:
    # @param A, a list of integers
    # @param target, an integer to be inserted
    # @return integer
    def searchInsert(self, A, target):
        l = 0
        r = len(A) - 1
        pos = 0
        while l <= r:
            mid = l + (r - l) / 2
            if A[mid] > target:
                r = mid - 1
                pos = mid
            elif A[mid] < target:
                l = mid + 1
                pos = mid + 1
            else:
                return mid
        return pos


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.searchInsert([], 1), 0)
        assert_equal(s.searchInsert([1], 1), 0)
        assert_equal(s.searchInsert([2], 1), 0)
        assert_equal(s.searchInsert([1], 2), 1)

    def test_example(self):
        s = Solution()
        assert_equal(s.searchInsert([1,3,5,6], 5), 2)
        assert_equal(s.searchInsert([1,3,5,6], 2), 1)
        assert_equal(s.searchInsert([1,3,5,6], 7), 4)
        assert_equal(s.searchInsert([1,3,5,6], 0), 0)
        assert_equal(s.searchInsert([1,3], 2), 1)
