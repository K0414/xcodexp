from nose.tools import assert_equal

class Solution:
    # @param A, a list of integer
    # @return an integer
    def singleNumber(self, A):
        """
        An explanation to the Solution could be found at:
        https://oj.leetcode.com/discuss/857/constant-space-solution.
        """
        return self._solve1(A)
        return self._solve2(A)
        return self._solve_general(A)

    def _solve1(self, A):
        res = 0
        for i in range(32):
            count = 0
            for j in A:
                if (j & 1 << i):
                    count += 1
            res |= ((count % 3) << i)
        return res if (res < 0x80000000) else (res - 0x100000000)

    def _solve2(self, A):
        ones = 0
        twos = 0
        threes = 0
        for n in A:
            twos |= ones & n
            ones ^= n
            threes = ones & twos
            ones &= ~threes
            twos &= ~threes
        return ones

    def _solve_general(self, A):
        """
        The general version of the question would be:

            Given an array of integers, every element appears k times except for one.
            Find that single one who appears l times.

        We need a array x[i] with size k for saving the bits appears i times.
        For every input number a, generate the new counter by
        x[j] = (x[j-1] & a) | (x[j] & ~a). Except x[0] = (x[k] & a) | (x[0] & ~a).

        In the equation, the first part indicates the the carries from previous one.
        The second part indicates the bits not carried to next one.

        Then the algorithms run in O(kn) and the extra space O(k).
        """


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.singleNumber([5]), 5)
        assert_equal(s.singleNumber([3,3,5,3]), 5)
        assert_equal(s.singleNumber([3,19837,3,19837,5,3,19837]), 5)

    def test_example(self):
        s = Solution()
        assert_equal(s.singleNumber([-2,-2,1,1,-3,1,-3,-3,-4,-2]), -4)
