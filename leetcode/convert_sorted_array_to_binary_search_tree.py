from nose.tools import assert_less_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param num, a list of integers
    # @return a tree node
    def sortedArrayToBST(self, num):
        return self._convert_recursive(num, 0, len(num)-1)

    def _convert_recursive(self, num, l, r):
        if l > r:
            return None
        if l == r:
            return TreeNode(num[l])

        mid = l + (r - l) / 2
        n = TreeNode(num[mid])
        n.left = self._convert_recursive(num, l, mid-1)
        n.right = self._convert_recursive(num, mid+1, r)
        return n


class TestSolution(object):

    def _assert(self, root):
        if not root:
            return
        if root.left:
            assert_less_equal(root.left.val, root.val)
            self._assert(root.left)
        if root.right:
            assert_less_equal(root.val, root.right.val)
            self._assert(root.right)

    def test_simple(self):
        s = Solution()
        n = s.sortedArrayToBST([])
        self._assert(n)
        n = s.sortedArrayToBST([1,1,1,1,1,1,1])
        self._assert(n)
        n = s.sortedArrayToBST([1,1,1,1,1,1,1,1])
        self._assert(n)
        n = s.sortedArrayToBST([1,2,3,4,5,6,7])
        self._assert(n)
        n = s.sortedArrayToBST([1,2,2,3,3,4,5,5])
        self._assert(n)

    def test_example(self):
        pass
