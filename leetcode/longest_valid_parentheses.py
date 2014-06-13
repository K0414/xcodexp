from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @return an integer
    def longestValidParentheses(self, s):
        #return self._solve_nn(s)
        return self._solve_dp(s)

    def _solve_dp(self, s):
        if not s: return 0
        dp = [0] * len(s)
        for i in range(len(s)-1)[::-1]:
            if s[i] == '(':
                pos = i + dp[i+1] + 1
                if pos < len(s) and s[pos] == ')':
                    dp[i] = dp[i+1] + 2
                    if pos + 1 < len(s):
                        dp[i] += dp[pos + 1]
        return max(dp)

    def _solve_nn(self, s):
        maxlen = 0
        self.memo = {}
        for i in range(len(s)):
            if i in self.memo:
                continue
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
                        maxlen = max(maxlen, j - start)
                        start = j+1
                        self.memo[start] = 1
            maxlen = max(maxlen, len(s) - start - (2 * count + len(stack)))
        return maxlen


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
