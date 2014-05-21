"""
  nextPermutation consists of the following steps:
  1) Reverse find the first element 'e' that breaks the descending order.
  2) If not found, reverse the whole list and return.
  3) In the visited elements, select a set whose value is larger than 'e',
     pick the smallest among the set and swap it with 'e'.
  4) Reverse all the elements after 'e'.

                  5               5
                    4     ->        3     ->  1 4 2 3 5
              1 3     2       1 4     2

"""

from nose.tools import assert_equal

class Solution:
    # @param num, a list of integer
    # @return a list of integer
    def nextPermutation(self, num):
        for i in range(len(num)-1, 0, -1):
            if num[i] > num[i-1]:
                j = i
                while j < len(num) and num[j] > num[i-1]:
                    j += 1
                t = num[i-1]
                num[i-1] = num[j-1]
                num[j-1] = t
                self._reverse(num, i, len(num)-1)
                return num
        num.reverse()
        return num

    def _reverse(self, num, start, end):
        while start < end:
            t = num[start]
            num[start] = num[end]
            num[end] = t
            start += 1
            end -= 1
        return num


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.nextPermutation([]), [])
        assert_equal(s.nextPermutation([1]), [1])
        assert_equal(s.nextPermutation([1,1,1]), [1,1,1])
        assert_equal(s.nextPermutation([1,3,2]), [2,1,3])
        assert_equal(s.nextPermutation([4,1,3,2]), [4,2,1,3])
        assert_equal(s.nextPermutation([5,1,3,2,4]), [5,1,3,4,2])
        assert_equal(s.nextPermutation([5,1,4,3,2]), [5,2,1,3,4])
        assert_equal(s.nextPermutation([2,3,1]), [3,1,2])


    def test_example(self):
        s = Solution()
        assert_equal(s.nextPermutation([1,2,3]), [1,3,2])
        assert_equal(s.nextPermutation([3,2,1]), [1,2,3])
        assert_equal(s.nextPermutation([1,1,5]), [1,5,1])
