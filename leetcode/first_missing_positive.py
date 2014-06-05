from nose.tools import assert_equal

class Solution:
    # @param A, a list of integers
    # @return an integer
    def firstMissingPositive(self, A):
        """
        Move positive values to its corresponding position if possible.
        """
        if not A: return 1
        i = 0
        while i < len(A):
            # If values are the same, no need to swap.
            if A[i] > 0 and A[i] <= len(A) and A[A[i]-1] != A[i]:
                A[A[i]-1], A[i] = A[i], A[A[i]-1]
            else:
                i += 1
        if A[0] != 1:
            return 1
        for i in range(len(A)):
            if A[i] != i+1:
                return i+1
        return A[-1] + 1


class TestSoution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.firstMissingPositive([]), 1)
        assert_equal(s.firstMissingPositive([0]), 1)
        assert_equal(s.firstMissingPositive([2,0,1]), 3)
        assert_equal(s.firstMissingPositive([1,2,3,4,5]), 6)
        assert_equal(s.firstMissingPositive([0,1,2,3,4,5]), 6)
        assert_equal(s.firstMissingPositive([-10,12,6,1,-5,-9,102]), 2)
        assert_equal(s.firstMissingPositive([102,101,105,97,128,4096]), 1)

    def test_example(self):
        s = Solution()
        assert_equal(s.firstMissingPositive([1,2,0]), 3)
        assert_equal(s.firstMissingPositive([3,4,-1,1]), 2)
        assert_equal(s.firstMissingPositive([1,1]), 2)
