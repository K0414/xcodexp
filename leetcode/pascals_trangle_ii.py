from nose.tools import assert_equal

class Solution:
    # @return a list of integers
    def getRow(self, rowIndex):
        return self._getRow(rowIndex)

        rowIndex += 1
        row = [1] * rowIndex
        for i in range(3, rowIndex+1):
            for j in range(1, (i+1)/2):
                if i % 2 == 1 and j == i / 2:
                    row[j] = 2 * row[-j]
                else:
                    row[j] = row[-j] + row[-j-1]
            for j in range(1, (i+1)/2):
                row[-1-j] = row[j]
        return row

    # A more elegant solution by CCLeaves.
    def _getRow(self, rowIndex):
        res = [1]
        for i in range(1, rowIndex+1):
            res.append(1)
            for j in range(1, i)[::-1]:
                res[j] += res[j-1]
        return res


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.getRow(0), [1])
        assert_equal(s.getRow(1), [1,1])
        assert_equal(s.getRow(2), [1,2,1])
        assert_equal(s.getRow(3), [1,3,3,1])
        assert_equal(s.getRow(4), [1,4,6,4,1])
        assert_equal(s.getRow(5), [1,5,10,10,5,1])
        assert_equal(s.getRow(6), [1,6,15,20,15,6,1])
        assert_equal(s.getRow(7), [1,7,21,35,35,21,7,1])
        assert_equal(s.getRow(8), [1,8,28,56,70,56,28,8,1])

    def test_example(self):
        pass
