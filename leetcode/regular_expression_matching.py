from nose.tools import assert_equal

class Solution:
    # @return a boolean
    def isMatch(self, s, p):
        #return self._solve_backtrace(s, p)
        return self._solve_nfa(s, p)

    def _solve_backtrace(self, s, p):
        while s and p and p[-1] != '*':
            if (p[-1] != s[-1] and p[-1] != '.'):
                return False
            p = p[:-1]
            s = s[:-1]
        return self._matchhere(s, p)

    def _matchhere(self, s, p):
        if not s and not p: return True
        if not p: return False
        if len(p) > 1 and p[1] == '*':
            return self._matchstar(p[0], s, p[2:])
        if s and (p[0] == s[0] or p[0] == '.'):
            return self._matchhere(s[1:], p[1:])
        return False

    def _matchstar(self, c, s, p):
        i = 0
        while i < len(s) and (c == s[i] or c == '.'):
            i += 1
            if self._matchhere(s[i:], p):
                return True
        return self._matchhere(s, p)

    def _solve_nfa(self, s, p):
        class State(object):
            Match = 256
            def __init__(self, c):
                self.char = c
                self.out1 = None
                self.out2 = None
        def _build_nfa(regexp):
            """
            Since we only support '.' and '*' operators, no conversion to reverse
            polish notation is needed. We can use a single pass scan to build the
            NFA directly.
            """
            head = State('^')
            states = [ head ]
            for c in regexp:
                if c == '*':
                    e = states.pop()
                    # Invalid regexp, '*' appears at the start.
                    if e == head: return None
                    s = State('*')
                    s.out2 = e
                    e.out1 = s
                    states[-1].out1 = s
                    states.append(s)
                else:
                    s = State(c)
                    states[-1].out1 = s
                    states.append(s)
            states[-1].out1 = State(State.Match)
            return states[0].out1
        def _match(text, nfa):
            statcurr = [ nfa ]
            statnext = []
            for c in text:
                while statcurr:
                    s = statcurr.pop(0)
                    if s.char == '.' or s.char == c:
                        statnext.append(s.out1)
                    elif s.char == '*':
                        if s.out1 not in statcurr:
                            statcurr.append(s.out1)
                        if s.out2 not in statcurr:
                            statcurr.append(s.out2)
                statcurr, statnext = statnext, []
            for s in statcurr:
                if s.char == State.Match:
                    return True
                if s.char == '*':
                    statcurr.append(s.out1)
                    statcurr.append(s.out2)
            return False
        nfa = _build_nfa(p)
        if not nfa: return False
        return _match(s, nfa)


class TestSolution(object):

    def test_backtrace(self):
        s = Solution()
        self._simple(s._solve_backtrace)
        self._example(s._solve_backtrace)

    def test_nfa(self):
        s = Solution()
        self._simple(s._solve_nfa)
        self._example(s._solve_nfa)

    def _simple(self, func):
        assert_equal(func("", ""), True)
        assert_equal(func("a", "a"), True)
        assert_equal(func("a", "b"), False)
        assert_equal(func("aab", "a*b"), True)
        assert_equal(func("aaab", "a*b"), True)
        assert_equal(func("aaaababac", "a*b*a*b*a*c"), True)
        assert_equal(func("aaaababac", "a*d*b*a*b*a*c"), True)
        assert_equal(func("aaaababac", ".*c"), True)
        assert_equal(func("aaaababac", "a*.*c"), True)
        assert_equal(func("aaaababac", "a*db*a*b*a*c"), False)
        assert_equal(func("aaaababac", ".*"), True)
        assert_equal(func("abcdef", "abc"), False)
        assert_equal(func("abc", "abcdef"), False)

    def _example(self, func):
        assert_equal(func("aa", "a"), False)
        assert_equal(func("aa", "aa"), True)
        assert_equal(func("aaa", "aa"), False)
        assert_equal(func("aa", "a*"), True)
        assert_equal(func("aa", ".*"), True)
        assert_equal(func("ab", ".*"), True)
        assert_equal(func("aab", "c*a*b"), True)
        assert_equal(func("ab", ".*b"), True)
        assert_equal(func("ab", ".*c"), False)
        assert_equal(func("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c"), False)
        assert_equal(func("aaa", "ab*a"), False)

