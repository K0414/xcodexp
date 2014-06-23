from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return an integer
    def sumNumbers(self, root):
        return self._solve(root, 0)

    def _solve(self, root, sum):
        if not root:
            return sum
        if not root.left and not root.right:
            return sum * 10 + root.val
        if root.left and root.right:
            return self._solve(root.left, sum * 10 + root.val) \
                   + self._solve(root.right, sum * 10 + root.val)
        if root.left:
            return self._solve(root.left, sum * 10 + root.val)
        if root.right:
            return self._solve(root.right, sum * 10 + root.val)


import helper
class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.sumNumbers(None), 0)
        root = helper.Tree.deserialize([1])
        assert_equal(s.sumNumbers(root), 1)

    def test_example(self):
        s = Solution()
        root = helper.Tree.deserialize([1,2,3])
        assert_equal(s.sumNumbers(root), 25)
