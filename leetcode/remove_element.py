from nose.tools import assert_equal

class Solution:
    # @param    A       a list of integers
    # @param    elem    an integer, value need to be removed
    # @return an integer
    def removeElement(self, A, elem):
        l = 0
        r = len(A) - 1
        while l <= r:
            if A[l] == elem:
                A[l], A[r] = A[r], A[l]
                r -= 1
            else:
                l += 1
        return (r + 1)

class TestSolution(object):

    def test_simple(self):
        s = Solution()
        a = []
        l = s.removeElement(a, 5)
        b = a[:l]
        assert_equal(b, [])
        a = [1,1,1,1,1]
        l = s.removeElement(a, 1)
        b = a[:l]
        assert_equal(b, [])
        a = [1,2,3,4,5,4,3]
        l = s.removeElement(a, 3)
        b = a[:l]
        assert_equal(b, [1,2,4,4,5])

    def test_example(self):
        pass
