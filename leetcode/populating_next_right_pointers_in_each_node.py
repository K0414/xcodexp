from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None

class Solution:
    # @param root, a tree node
    # @return nothing
    def connect(self, root):
        #self._solve_recursive(root)
        self._solve_loop(root)

    def _solve_recursive(self, root):
        if not root: return
        l = root.left
        r = root.right
        while l:
            l.next = r
            l = l.right
            r = r.left
        self._solve_recursive(root.left)
        self._solve_recursive(root.right)

    def _solve_loop(self, root):
        """
        Use previously connected link to traverse level by level.
        """
        while root and root.left:
            n = root
            p = None
            while n:
                n.left.next = n.right
                if p:
                    p.right.next = n.left
                p = n
                n = n.next
            root = root.left


class TestSolution(object):

    def test_simple(self):
        s = Solution()

    def test_example(self):
        s = Solution()
        root = TreeNode(1)
        root.left = TreeNode(2)
        root.right = TreeNode(3)
        root.left.left = TreeNode(4)
        root.left.right = TreeNode(5)
        root.right.left = TreeNode(6)
        root.right.right = TreeNode(7)
        s.connect(root)
        p = root
        assert_equal(p.val, 1)
        p = root.left
        assert_equal(p.val, 2)
        p = p.next
        assert_equal(p.val, 3)
        p = root.left.left
        assert_equal(p.val, 4)
        p = p.next
        assert_equal(p.val, 5)
        p = p.next
        assert_equal(p.val, 6)
        p = p.next
        assert_equal(p.val, 7)
