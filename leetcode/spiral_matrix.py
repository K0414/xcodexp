from nose.tools import assert_equal

class Solution:
    # @param matrix, a list of lists of integers
    # @return a list of integers
    def spiralOrder(self, matrix):
        if not matrix:
            return []

        result = []
        m = len(matrix)
        n = len(matrix[0])
        i, j = 0, 0
        bound = [n, m, -1, -1] # (right, bottom, left, top)
        while True:
            for step in range(4):
                if (bound[1] - bound[3] == 1) or (bound[0] - bound[2] == 1):
                    return result

                if step == 0:   # right
                    while j < bound[0]:
                        result.append(matrix[i][j])
                        j += 1
                    i += 1
                    j -= 1
                    bound[3] += 1
                elif step == 1: # down
                    while i < bound[1]:
                        result.append(matrix[i][j])
                        i += 1
                    i -= 1
                    j -= 1
                    bound[0] -= 1
                elif step == 2: # left
                    while j > bound[2]:
                        result.append(matrix[i][j])
                        j -= 1
                    i -= 1
                    j += 1
                    bound[1] -= 1
                else:           # up
                    while i > bound[3]:
                        result.append(matrix[i][j])
                        i -= 1
                    i += 1
                    j += 1
                    bound[2] += 1


class TestSolution(object):

    def test_empty(self):
        s = Solution()
        assert_equal(s.spiralOrder([]), [])
        assert_equal(s.spiralOrder([[]]), [])
        assert_equal(s.spiralOrder([[], []]), [])
        assert_equal(s.spiralOrder([[], [], []]), [])

    def test_square(self):
        s = Solution()
        m = [ [ 1, 2, 3 ],
              [ 4, 5, 6 ],
              [ 7, 8, 9 ] ]
        r = [1, 2, 3, 6, 9, 8, 7, 4, 5]
        assert_equal(s.spiralOrder(m), r)
        m = [ [  1,  2,  3 ],
              [  4,  5,  6 ],
              [  7,  8,  9 ],
              [ 10, 11, 12 ] ]
        r = [1, 2, 3, 6, 9, 12, 11, 10, 7, 4, 5, 8]
        assert_equal(s.spiralOrder(m), r)
        m = [ [ 1,  2,  3,  4 ],
              [ 5,  6,  7,  8 ],
              [ 9, 10, 11, 12 ] ]
        r = [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
        assert_equal(s.spiralOrder(m), r)
        m = [ [  1,  2,  3,  4 ],
              [  5,  6,  7,  8 ],
              [  9, 10, 11, 12 ],
              [ 13, 14, 15, 16 ] ]
        r = [1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10]
        assert_equal(s.spiralOrder(m), r)
