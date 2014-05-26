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
    def minDepth(self, root):
        if not root: return 0
        q = []
        qn = []
        q.append(root)
        level = 1
        while True:
            for n in q:
                if not n.left and not n.right:
                    return level
                if n.left: qn.append(n.left)
                if n.right: qn.append(n.right)
            level += 1
            q, qn = qn, []
        return level


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.minDepth(None), 0)
        assert_equal(s.minDepth(TreeNode(0)), 1)
        n = TreeNode(0)
        n.left = TreeNode(0)
        n.right = TreeNode(0)
        assert_equal(s.minDepth(n), 2)
        n.left.left = TreeNode(0)
        n.right.right = TreeNode(0)
        assert_equal(s.minDepth(n), 3)

    def test_example(self):
        pass
