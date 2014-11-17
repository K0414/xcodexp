from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def lengthOfLastWord(self, s):
        length = 0
        trim = True
        for i in range(len(s))[::-1]:
            if s[i] != ' ':
                length += 1
                trim = False
            elif not trim:
                break
        return length

class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.lengthOfLastWord(""), 0)
        assert_equal(s.lengthOfLastWord(" "), 0)
        assert_equal(s.lengthOfLastWord("  "), 0)

    def test_example(self):
        s = Solution()
        assert_equal(s.lengthOfLastWord("Hello World"), 5)
        assert_equal(s.lengthOfLastWord("Hi World"), 5)
        assert_equal(s.lengthOfLastWord("a "), 1)
