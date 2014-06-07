from nose.tools import assert_equal

class Solution:
    # @param height, a list of integer
    # @return an integer
    def largestRectangleArea(self, height):
        #return self._solve_naive(height)
        #return self._solve_dc(height)
        return self._solve_stack(height)

    def _solve_naive(self, height):
        maxArea = 0
        for i in range(len(height)):
            m = height[i]
            for j in range(i, len(height)):
                m = min(m, height[j])
                area = m * (j-i+1)
                maxArea = max(maxArea, area)
        return maxArea

    def _solve_stack(self, height):
        stack = []
        maxArea = 0
        for i in range(len(height)):
            while stack and height[stack[-1]] > height[i]:
                tp = stack[-1]
                stack.pop()
                ln = (i - stack[-1] - 1) if stack else i
                maxArea = max(maxArea, height[tp] * ln)
            stack.append(i)
        while stack:
            tp = stack[-1]
            stack.pop()
            ln = (len(height) - stack[-1] - 1) if stack else len(height)
            maxArea = max(maxArea, height[tp] * ln)
        return maxArea

    def _solve_dc(self, height):
        """
        Time for building segment tree is T(n) = 2T(n/2) + O(1), according to
        master theorem the time complexity is O(n).
        For querys, at each level at most 2 routines goes to the next level,
        so the time complexity is O(lg(n)).
        For the divide and conquer approach, n querys needs to be taken, which
        leads to a O(nlg(n)) time complexity.
        Thus the over all time complexity is O(n) + O(nlg(n)) = O(nlg(n)).

        """
        if not height: return 0
        self._rmq_bulid(height)
        return self._dc(height, 0, len(height)-1)

    def _dc(self, height, l, r):
        if l > r: return 0
        if l == r: return height[l]
        ix = self._rmq(height, l, r)
        area = max(self._dc(height, l, ix-1), self._dc(height, ix+1, r))
        return max(area, height[ix] * (r-l+1))

    ########################################################
    ## The following lines implement a segment tree for RMQ.
    ########################################################
    def _rmq(self, array, s, e):
        l = 0
        r = len(array) - 1
        if s < l or e > r:
            raise IndexError("query index out of range.")
        return self._rmq_query(array, l, r, s, e, 0)

    def _rmq_query(self, array, l, r, s, e, ix):
        """
        Perform a log(n) query on segment tree.
        (l, r)  is the range of the array.
        (s, e)  is the range of the query.
        """
        if s <= l and r <= e:
            return self.segtree[ix]
        elif r < s or e < l:
            return -1
        else:
            mid = l + (r - l) / 2
            return self._min(array,
                             self._rmq_query(array, l, mid, s, e, 2 * ix + 1),
                             self._rmq_query(array, mid+1, r, s, e, 2 * ix + 2))

    def _rmq_bulid(self, array):
        """
        Allocate memory for segment tree.
        """
        from math import log, ceil
        self.segtree = [0] * (2 * int(pow(2, ceil(log(len(array))/log(2)))) - 1)
        l = 0
        r = len(array) - 1
        self._rmq_gentree(array, l, r, 0)

    def _rmq_gentree(self, array, l, r, s):
        """
        Recursively Build segment tree.
        (l, r)  is the range of the array.
        s       is the index of the tree node.
        """
        if l == r:
            self.segtree[s] = l
            return self.segtree[s]
        mid = l + (r - l) / 2
        self.segtree[s] = self._min(array,
                                    self._rmq_gentree(array, l, mid, s+s+1),
                                    self._rmq_gentree(array, mid+1, r, s+s+2))
        return self.segtree[s]

    def _min(self, array, ix1, ix2):
        if ix1 == -1:
            return ix2
        if ix2 == -1:
            return ix1
        if array[ix1] > array[ix2]:
            return ix2
        else:
            return ix1


class TestSolution(object):

    def test_naive(self):
        s = Solution()
        self._simple(s._solve_naive)
        self._example(s._solve_naive)

    def test_stack(self):
        s = Solution()
        self._simple(s._solve_stack)
        self._example(s._solve_stack)

    def test_dc(self):
        s = Solution()
        self._simple(s._solve_dc)
        self._example(s._solve_dc)

    def test_rmq(self):
        s = Solution()
        a = [1]
        s._rmq_bulid(a)
        assert_equal(s._rmq(a, 0, 0), 0)
        a = [1,2]
        s._rmq_bulid(a)
        assert_equal(s._rmq(a, 0, 0), 0)
        assert_equal(s._rmq(a, 0, 1), 0)
        assert_equal(s._rmq(a, 1, 1), 1)
        a = [2,1,5,6,2,3]
        s._rmq_bulid(a)
        assert_equal(s._rmq(a, 0, 5), 1)
        assert_equal(s._rmq(a, 1, 4), 1)
        assert_equal(s._rmq(a, 2, 3), 2)
        assert_equal(s._rmq(a, 2, 5), 4)

    def _simple(self, func):
        assert_equal(func([]), 0)
        assert_equal(func([1]), 1)
        assert_equal(func([1,2]), 2)
        assert_equal(func([1,2,3]), 4)
        assert_equal(func([1,2,3,2,1]), 6)
        assert_equal(func([1,2,9,2,1]), 9)
        assert_equal(func([1,2,8,8,9,2,1]), 24)
        assert_equal(func([1,2,0,2,1]), 2)
        assert_equal(func([1,2,0,3,1]), 3)
        assert_equal(func([8,9,7]), 21)

    def _example(self, func):
        assert_equal(func([2,1,5,6,2,3]), 10)
        assert_equal(func([2,1,2]), 3)
        assert_equal(func([5,4,1,2]), 8)
        assert_equal(func([4,2,0,3,2,5]), 6)
        assert_equal(func(range(500)), 62500)
