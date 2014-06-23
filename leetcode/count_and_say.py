from nose.tools import assert_equal

class Solution:
    # @return a string
    def countAndSay(self, n):
        s = '1'
        for i in range(2, n+1):
            s = self._next(s)
        return s

    def _next(self, s):
        nxt = []
        i = 0
        while i < len(s):
            c = s[i]
            j = i+1
            while j < len(s) and s[j] == s[i]:
                j += 1
            nxt.append(str(j-i))
            nxt.append(s[i])
            i = j
        return ''.join(nxt)


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.countAndSay(6), '312211')

    def test_example(self):
        s = Solution()
        assert_equal(s.countAndSay(1), '1')
        assert_equal(s.countAndSay(2), '11')
        assert_equal(s.countAndSay(3), '21')
        assert_equal(s.countAndSay(4), '1211')
        assert_equal(s.countAndSay(5), '111221')
