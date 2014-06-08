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
    def isSymmetric(self, root):
        return self._solve_recursive(root)
        return self._solve_loop(root)

    def _solve_loop(self, root):
        if not root:
            return True
        q1 = [ root.left ]
        q2 = [ root.right ]
        while q1:
            n1 = q1.pop(0)
            n2 = q2.pop(0)
            if not n1 and not n2:
                continue
            if not n1 or not n2:
                return False
            if n1.val != n2.val:
                return False
            q1.append(n1.left)
            q1.append(n1.right)
            q2.append(n2.right)
            q2.append(n2.left)
        return True


    def _solve_recursive(self, root):
        if not root: return True
        return self._solve_lr(root.left, root.right)

    def _solve_lr(self, l, r):
        if not l and not r:
            return True
        if not l or not r:
            return False
        if l.val != r.val:
            return False
        return self._solve_lr(l.left, r.right) and self._solve_lr(l.right, r.left)

class TestSolution(object):

    def test_recursive(self):
        s = Solution()
        self._simple(s.isSymmetric)
        self._example(s.isSymmetric)

    def test_loop(self):
        s = Solution()
        self._simple(s._solve_loop)
        self._example(s._solve_loop)

    def _simple(self, func):
        root = TreeNode(1)
        root.left = TreeNode(2)
        root.right = TreeNode(2)
        root.left.left = TreeNode(3)
        root.left.right = TreeNode(4)
        root.right.left = TreeNode(3)
        root.right.right = TreeNode(4)
        assert_equal(func(root), False)

    def _example(self, func):
        root = TreeNode(1)
        assert_equal(func(root), True)
        root.left = TreeNode(2)
        assert_equal(func(root), False)
        root.right = TreeNode(2)
        assert_equal(func(root), True)
        root.left.left = TreeNode(3)
        assert_equal(func(root), False)
        root.left.right = TreeNode(4)
        assert_equal(func(root), False)
        root.right.left = TreeNode(4)
        assert_equal(func(root), False)
        root.right.right = TreeNode(3)
        assert_equal(func(root), True)

        root = TreeNode(1)
        root.left = TreeNode(2)
        root.right = TreeNode(2)
        root.left.right = TreeNode(3)
        assert_equal(func(root), False)
        root.right.right = TreeNode(3)
        assert_equal(func(root), False)
