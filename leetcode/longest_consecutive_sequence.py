from nose.tools import assert_equal

class Solution:
    # @param num, a list of integer
    # @return an integer
    def longestConsecutive(self, num):
        #return self._solve_sort(num)
        return self._solve_hash(num)

    def _solve_hash(self, num):
        tab = {}
        for n in num:
            tab[n] = 1
        maxl = 1
        for n in num:
            count = 1
            t = n - 1
            while t in tab:
                del tab[t]
                count += 1
                t -= 1
            t = n + 1
            while t in tab:
                del tab[t]
                count += 1
                t += 1
            maxl = max(maxl, count)
        return maxl

    def _solve_sort(self, num):
        num.sort()
        #num = self._bucket_sort_c_style(num)
        maxl = 1
        c = 1
        for i in range(1, len(num)):
            if num[i] == num[i-1]:
                continue
            if num[i] == num[i-1]+1:
                c += 1
                maxl = max(c, maxl)
            else:
                c = 1
        return maxl

#    def _bucket_sort_c_style(self, num):
#        if not num: return []
#        # 0) Get range. (not necessary in python.)
#        mi = num[0]
#        ma = num[0]
#        for n in num:
#            mi = min(n, mi)
#            ma = max(n, ma)
#        length = ma - mi + 1
#        count = [0] * (length+1)
#        # 1) Count.
#        for n in num:
#            idx = n-mi
#            count[idx+1] += 1
#        # 2) Accumulate.
#        for k in range(1, length+1):
#            count[k] += count[k-1]
#        # 3) Move.
#        temp = [0] * len(num)
#        for i in range(len(num)):
#            idx = num[i]-mi
#            temp[count[idx]] = num[i]
#            count[idx] += 1
#        return temp


class TestSolution(object):

    def notest_bucket_sort(self):
        s = Solution()
        assert_equal(s._bucket_sort_c_style([]), [])
        assert_equal(s._bucket_sort_c_style([0]), [0])
        assert_equal(s._bucket_sort_c_style([0,1]), [0,1])
        assert_equal(s._bucket_sort_c_style([1,0]), [0,1])
        assert_equal(s._bucket_sort_c_style([100,4,200,1,3,2]), [1,2,3,4,100,200])

    def test_simple(self):
        s = Solution()
        assert_equal(s.longestConsecutive([0]), 1)

    def test_example(self):
        s = Solution()
        assert_equal(s.longestConsecutive([100, 4, 200, 1, 3, 2]), 4)
        assert_equal(s.longestConsecutive([1,2,0,1]), 3)
