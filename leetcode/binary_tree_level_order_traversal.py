from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return a list of lists of integers
    def levelOrder(self, root):
        if not root: return []
        q1 = [ root ]
        q2 = []
        result = []
        while q1:
            result.append([])
            for n in q1:
                result[-1].append(n.val)
                if n.left:
                    q2.append(n.left)
                if n.right:
                    q2.append(n.right)
            q1, q2 = q2, []
        return result


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        root = TreeNode(0)
        assert_equal(s.levelOrder(root), [[0]])
        root.left = TreeNode(1)
        assert_equal(s.levelOrder(root), [[0], [1]])
        root.left.left = TreeNode(2)
        root.left.right = TreeNode(3)
        assert_equal(s.levelOrder(root), [[0], [1], [2,3]])

    def test_example(self):
        s = Solution()
        root = TreeNode(3)
        root.left = TreeNode(9)
        root.right = TreeNode(20)
        root.right.left = TreeNode(15)
        root.right.right = TreeNode(7)
        assert_equal(s.levelOrder(root), [[3], [9,20], [15,7]])
