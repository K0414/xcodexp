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
    def maxDepth(self, root):
        self.depth = 0
        self._visit(root, 0)
        return self.depth

    def _visit(self, root, depth):
        if not root:
            if depth > self.depth:
                self.depth = depth
            return
        self._visit(root.left, depth + 1)
        self._visit(root.right, depth + 1)


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.maxDepth(None), 0)
        root = TreeNode(0)
        assert_equal(s.maxDepth(root), 1)
        root.left = TreeNode(0)
        root.right = TreeNode(0)
        assert_equal(s.maxDepth(root), 2)
        root.right.left = TreeNode(0)
        assert_equal(s.maxDepth(root), 3)

    def test_example(self):
        s = Solution()
