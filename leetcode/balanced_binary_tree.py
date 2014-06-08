from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return a boolean
    def isBalanced(self, root):
        if not root: return True
        return self._solve(root, 0) != -1

    def _solve(self, root, level):
        if not root:
            return level
        l = self._solve(root.left, level+1)
        r = self._solve(root.right, level+1)
        if abs(l-r) > 1:
            return -1
        else:
            return max(l, r)



class TestSolution(object):

    def test_simple(self):
        s = Solution()
        root = TreeNode(0)
        assert_equal(s.isBalanced(root), True)
        root.left = TreeNode(0)
        assert_equal(s.isBalanced(root), True)
        root.right = TreeNode(0)
        assert_equal(s.isBalanced(root), True)
        root.right.left = TreeNode(0)
        assert_equal(s.isBalanced(root), True)
        root.right.left.right = TreeNode(0)
        assert_equal(s.isBalanced(root), False)

    def test_example(self):
        s = Solution()
