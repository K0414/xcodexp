from nose.tools import assert_equal

class Solution:
    # @return a boolean
    def isPalindrome(self, x):
        if x < 0: return False
        div = 1
        while x / div:
            div *= 10
        div /= 10
        while div:
            if (x / div) != (x % 10):
                return False
            x = (x % div) / 10
            div /= 100
        return True


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.isPalindrome(0), True)
        assert_equal(s.isPalindrome(1), True)
        assert_equal(s.isPalindrome(11), True)
        assert_equal(s.isPalindrome(12), False)
        assert_equal(s.isPalindrome(121), True)
        assert_equal(s.isPalindrome(122), False)
        assert_equal(s.isPalindrome(1221), True)
        assert_equal(s.isPalindrome(1222), False)
        assert_equal(s.isPalindrome(123454321), True)
        assert_equal(s.isPalindrome(123455321), False)

    def test_example(self):
        s = Solution()
        assert_equal(s.isPalindrome(-2147447412), False)
