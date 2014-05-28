from nose.tools import assert_equal

class Solution:
    # @param s, a string
    # @param dict, a set of string
    # @return a list of strings
    def wordBreak(self, s, dict):
        self.segs = []
        self.pos = []
        for i in range(len(s)):
            self.pos.append(len(self.segs))
            for j in range(i, len(s)):
                if s[i:j+1] in dict:
                    self.segs.append((i, j))
        self.results = []
        self.one = []
        self.can = [True] * len(s)
        self._pick(0, s)
        return self.results

    def _pick(self, start, s):
        if start == len(s):
            ss = []
            for p in self.one:
                ss.append(s[p[0]:p[1]+1])
            self.results.append(' '.join(ss))
            return

        if not self.can[start]:
            return
        for p in self.segs[self.pos[start]:]:
            if p[0] != start:
                break
            self.one.append(p)
            os = len(self.results)
            self._pick(p[1]+1, s)
            if os == len(self.results):
                self.can[p[1]+1] = False
            self.one.pop()


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        t = "aaaaa"
        d = ["a"]
        r = ["a a a a a"]
        r.sort()
        assert_equal(s.wordBreak(t, d), r)
        t = "aaa"
        d = ["a", "aa"]
        r = ["a a a", "a aa", "aa a"]
        r.sort()
        assert_equal(s.wordBreak(t, d), r)

    def test_example(self):
        s = Solution()
        t = "catsanddog"
        d = ["cat", "cats", "and", "sand", "dog"]
        r = ["cats and dog", "cat sand dog"]
        r.sort()
        assert_equal(s.wordBreak(t, d), r)
        t = "aaaaaaaa"
        d = ["aaaa","aaa","aa"]
        r = ["aa aa aa aa","aaaa aa aa","aaa aaa aa","aa aaaa aa","aaa aa aaa","aa aaa aaa","aa aa aaaa","aaaa aaaa"]
        r.sort()
        assert_equal(s.wordBreak(t, d), r)

if __name__=='__main__':
        s = Solution()
        t = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
        d = ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
        print s.wordBreak(t, d)

