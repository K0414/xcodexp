from nose.tools import assert_equal

class Solution:
    # @return a list of lists of integer
    def generateMatrix(self, n):
        c = 1
        # [left, top, right, bottom]
        bound = [0, 0, n-1, n-1]
        result = [ [0] * n for i in range(n) ]
        while c <= n*n:
            # left -> right
            for i in range(bound[0], bound[2]+1):
                result[bound[1]][i] = c
                c += 1
            bound[1] += 1

            # top -> bottom
            for i in range(bound[1], bound[3]+1):
                result[i][bound[2]] = c
                c += 1
            bound[2] -= 1

            # right -> left
            for i in range(bound[0], bound[2]+1)[::-1]:
                result[bound[3]][i] = c
                c += 1
            bound[3] -= 1

            # bottom -> top
            for i in range(bound[1], bound[3]+1)[::-1]:
                result[i][bound[0]] = c
                c += 1
            bound[0] += 1
        return result


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        m = [ [ 1 ] ]
        assert_equal(s.generateMatrix(1), m)
        m = [ [ 1, 2 ],
              [ 4, 3 ] ]
        assert_equal(s.generateMatrix(2), m)
        m = [ [ 1, 2, 3 ],
              [ 8, 9, 4 ],
              [ 7, 6, 5 ] ]
        assert_equal(s.generateMatrix(3), m)
        m = [ [  1,  2,  3,  4 ],
              [ 12, 13, 14,  5 ],
              [ 11, 16, 15,  6 ],
              [ 10,  9,  8,  7 ] ]
        assert_equal(s.generateMatrix(4), m)

    def test_square(self):
        pass
