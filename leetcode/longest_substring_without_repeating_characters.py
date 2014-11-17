from nose.tools import assert_equal

class Solution:
    # @return an integer
    def lengthOfLongestSubstring(self, s):
        posMap = {}
        maxlen = 0
        start = 0
        for i in range(len(s)):
            if s[i] not in posMap: posMap[s[i]] = -1
            if posMap[s[i]] >= start:
                maxlen = max(maxlen, i - start)
                start = posMap[s[i]] + 1
            posMap[s[i]] = i
        return max(maxlen, len(s) - start)



class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.lengthOfLongestSubstring(''), 0)

    def test_example(self):
        s = Solution()
        assert_equal(s.lengthOfLongestSubstring('bbbb'), 1)
        assert_equal(s.lengthOfLongestSubstring('abcabcbb'), 3)
