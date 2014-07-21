from nose.tools import assert_equal

class Solution:
    # @param A, a list of integers
    # @param target, an integer to be searched
    # @return a list of length 2, [index1, index2]
    def searchRange(self, A, target):
        start = 0
        end = len(A) - 1
        while start <= end:
            mid = start + (end - start) / 2
            if A[mid] < target:
                start = mid + 1
            elif A[mid] > target:
                end = mid - 1
            else:
                s = self._start(A, start, mid, target)
                e = self._end(A, mid, end, target)
                return [s, e]
        return [-1, -1]

    def _start(self, A, start, end, target):
        while start <= end and A[start] != target:
            mid = start + (end - start) / 2
            if A[mid] == target:
                end = mid - 1
            else:
                start = mid + 1
        return start

    def _end(self, A, start, end, target):
        while start <= end and A[end] != target:
            mid = start + (end - start) / 2
            if A[mid] == target:
                start = mid + 1
            else:
                end = mid - 1
        return end


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.searchRange([], 8), [-1, -1])
        assert_equal(s.searchRange([5], 8), [-1, -1])

    def test_example(self):
        s = Solution()
        assert_equal(s.searchRange([5, 7, 7, 8, 8, 10], 8), [3, 4])
