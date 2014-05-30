from nose.tools import assert_equal

class Solution:
    # @return a list of lists of length 3, [[val1,val2,val3]]
    def threeSum(self, num):
        if not num: return num
        num.sort()
        results = []
        for i in range(len(num)-2):
            if sum(num[i:i+3]) > 0:
                break
            if i > 0 and num[i] == num[i-1]:
                continue
            one = []
            t = num[i]
            self._sum2(num[i+1:], -t, one)
            for o in one:
                results.append([t, o[0], o[1]])
        return results

    def _sum2(self, num, target, results):
        l = 0
        r = len(num)-1
        while l < r:
            if num[l] + num[r] == target:
                results.append([num[l], num[r]])
                l += 1
                r -= 1
                while l < r and num[l] == num[l-1]:
                    l += 1
                while l < r and num[r] == num[r+1]:
                    r -= 1
            elif num[l] + num[r] > target:
                r -= 1
            else:
                l += 1


class TestSolution(object):

    def test_sum2(self):
        s = Solution()
        results = []
        s._sum2([1,2,3,4,5,6], 7, results)
        assert_equal(results, [[1,6],[2,5],[3,4]])

    def test_simple(self):
        s = Solution()
        assert_equal(s.threeSum([1,0,-1]), [[-1,0,1]])

    def test_example(self):
        s = Solution()
        assert_equal(s.threeSum([-1,0,1,2,-1,-4]), [[-1,-1,2],[-1,0,1]])
        assert_equal(s.threeSum([0,0,0]), [[0,0,0]])

if __name__=='__main__':
    s = Solution()
    print s.threeSum([7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6])
