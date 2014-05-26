from nose.tools import assert_equal

class Solution:
    # @param A  a list of integers
    # @param m  an integer, length of A
    # @param B  a list of integers
    # @param n  an integer, length of B
    # @return nothing
    def merge(self, A, m, B, n):
        A.extend(B)
        pos_a = m-1
        pos_b = n-1
        pos = m+n-1
        while pos_a >= 0 and pos_b >= 0:
            if A[pos_a] >= B[pos_b]:
                A[pos] = A[pos_a]
                pos_a -= 1
            else:
                A[pos] = B[pos_b]
                pos_b -= 1
            pos -= 1
        while pos_a >= 0:
            A[pos] = A[pos_a]
            pos_a -= 1
            pos -= 1
        while pos_b >= 0:
            A[pos] = B[pos_b]
            pos_b -= 1
            pos -= 1


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        la = []
        lb = []
        s.merge(la, len(la), lb, len(lb))
        assert_equal(la, [])
        la = [1]
        lb = []
        s.merge(la, len(la), lb, len(lb))
        assert_equal(la, [1])
        la = []
        lb = [1]
        s.merge(la, len(la), lb, len(lb))
        assert_equal(la, [1])
        la = [1,2,3]
        lb = [2,3,4]
        s.merge(la, len(la), lb, len(lb))
        assert_equal(la, [1,2,2,3,3,4])

    def test_example(self):
        pass
