from nose.tools import assert_equal

class Solution:
    # @param digits, a list of integer digits
    # @return a list of integer digits
    def plusOne(self, digits):
        carrier = 1
        for i in range(len(digits))[::-1]:
            if not carrier:
                break
            carrier = (digits[i] + 1) / 10
            digits[i] = (digits[i] + 1) % 10
        if carrier:
            digits.insert(0, 1)
        return digits


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.plusOne([]), [1])
        assert_equal(s.plusOne([1]), [2])
        assert_equal(s.plusOne([1,2,3]), [1,2,4])
        assert_equal(s.plusOne([1,0,2]), [1,0,3])
        assert_equal(s.plusOne([9,9,9]), [1,0,0,0])

    def test_example(self):
        s = Solution()
