from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return a boolean
    def isPalindrome(self, s):
        chars = [x for x in s.lower() if x.isalnum()]
        i, j = divmod(len(chars)-1, 2)
        j += i
        while i >= 0:
            if chars[i] != chars[j]:
                return False
            i -= 1
            j += 1
        return True


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.isPalindrome(''), True)
        assert_equal(s.isPalindrome('a'), True)
        assert_equal(s.isPalindrome('aa'), True)
        assert_equal(s.isPalindrome('aba'), True)
        assert_equal(s.isPalindrome('ab'), False)
        assert_equal(s.isPalindrome('abc'), False)

    def test_example(self):
        s = Solution()
        assert_equal(s.isPalindrome('A man, a plan, a canal: Panama'), True)
        assert_equal(s.isPalindrome('race a car'), False)
