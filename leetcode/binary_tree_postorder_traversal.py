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
    def postorderTraversal(self, root):
        self.result = []
        #self._solve_recursive(root)
        self._solve_loop(root)
        return self.result

    def _solve_recursive(self, root):
        if not root: return
        self._solve_recursive(root.left)
        self._solve_recursive(root.right)
        self.result.append(root.val)

    def _solve_loop(self, root):
        if not root: return
        stack = []
        lastVisited = None
        while root or stack:
            while root:
                stack.append(root)
                root = root.left
            root = stack[-1]
            if root.right and root.right != lastVisited:
                root = root.right
            else:
                self.result.append(root.val)
                stack.pop()
                lastVisited = root
                root = None

    def _solve_morris(self, root):
        pass


class TestSolution(object):

    def test_simple(self):
        import helper
        s = Solution()
        r = s.postorderTraversal(helper.Tree.deserialize([1]))
        assert_equal(r, [1])

    def test_example(self):
        import helper
        s = Solution()
        r = s.postorderTraversal(helper.Tree.deserialize([1,'#',2,3]))
        assert_equal(r, [3,2,1])
