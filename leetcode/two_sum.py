from nose.tools import assert_equal

class Solution:
    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        p = zip(num, range(1, len(num)+1))
        p.sort()
        i = 0
        j = len(p)-1
        while i < j:
            if p[i][0] + p[j][0] == target:
                ix1 = p[i][1]
                ix2 = p[j][1]
                return (ix1, ix2) if ix1 < ix2 else (ix2, ix1)
            elif p[i][0] + p[j][0] < target:
                i += 1
            else:
                j -= 1
        return (-1, -1)



class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.twoSum([2,7,11,15], 18), (2,3))
        assert_equal(s.twoSum([2,11,7,15], 26), (2,4))
        assert_equal(s.twoSum([2,15,7,11], 26), (2,4))

    def test_example(self):
        s = Solution()
        assert_equal(s.twoSum([2,7,11,15], 9), (1,2))
