from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def longestValidParentheses(self, s):
        return self._solve_nn(s)

    def _solve_nn(self, s):
        maxlen = 0
        for i in range(len(s)):
            # If the number of half parentheses is not enough,
            # break the loop in advance.
            rparen = 0
            lparen = 0
            for j in range(i, len(s)):
                if s[j] == ')':
                    rparen += 1
                else:
                    lparen += 1
            if rparen * 2 <= maxlen or lparen * 2 <= maxlen:
                break
            # Start counting.
            stack = []
            start = i
            count = 0
            for j in range(i, len(s)):
                if s[j] == '(':
                    stack.append('(')
                else:
                    if stack:
                        stack.pop()
                        count += 1
                        if not stack:
                            count = 0
                    else:
                        print j - start
                        maxlen = max(maxlen, j - start)
                        start = j+1
            maxlen = max(maxlen, len(s) - start - (2 * count + len(stack)))
        return maxlen

    def _solve_dc(self, s):
        pass


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.longestValidParentheses(''), 0)
        assert_equal(s.longestValidParentheses('('), 0)
        assert_equal(s.longestValidParentheses('('), 0)

    def test_example(self):
        s = Solution()
        assert_equal(s.longestValidParentheses('(()'), 2)
        assert_equal(s.longestValidParentheses(')()())'), 4)
        assert_equal(s.longestValidParentheses(')()(()('), 2)
        assert_equal(s.longestValidParentheses(')()(()())'), 8)
        assert_equal(s.longestValidParentheses(')()(()())('), 8)
        assert_equal(s.longestValidParentheses(')()(()()))'), 8)
        assert_equal(s.longestValidParentheses('(' * 20000), 0)
        assert_equal(s.longestValidParentheses(')' * 20000), 0)
