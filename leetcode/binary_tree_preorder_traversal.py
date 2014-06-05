from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return a list of integers
    def preorderTraversal(self, root):
        result = []
        #self.visit(root, result)
        self.visitloop(root, result)
        return result

    def visit(self, root, result):
        if not root:
            return

        result.append(root.val)
        self.visit(root.left, result)
        self.visit(root.right, result)

    def visitloop(self, root, result):
        if not root:
            return

        stack = [ root ]
        while stack:
            n = stack.pop()
            result.append(n.val)
            if n.right: stack.append(n.right)
            if n.left: stack.append(n.left)


class TestSolution(object):

    def test_example(self):
        root = TreeNode(1)
        root.left = None
        root.right = TreeNode(2)
        root.right.left = TreeNode(3)
        s = Solution()
        r = s.preorderTraversal(root)
        assert_equal(r, [1, 2, 3])

    def test_312(self):
        root = TreeNode(3)
        root.left = TreeNode(1)
        root.right = TreeNode(2)
        s = Solution()
        r = s.preorderTraversal(root)
        assert_equal(r, [3, 1, 2])
