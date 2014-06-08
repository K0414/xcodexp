from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return nothing, do it in place
    def flatten(self, root):
        if not root: return root
        #self._solve_recursive(root)
        self._solve_loop(root)
        return root

    def _solve_recursive(self, root):
        l = root.left
        r = root.right
        last = root
        if l:
            root.right = l
            root.left = None  # This line is needed to avoid TLE.
            last = self._solve_recursive(l)
            last.right = r
        if r:
            last = self._solve_recursive(r)
        return last

    def _solve_loop(self, root):
        p = root
        while p:
            if p.left:
                n = p.left
                while n.right:
                    n = n.right
                n.right = p.right
                p.right = p.left
                p.left = None
            p = p.right
        return root


class TestSolution(object):

    def _deserialize(self, lst):
        root = TreeNode(lst[0])
        q = [ root ]
        i = 1
        while i < len(lst):
            n = q.pop(0)
            if lst[i] != '#':
                n.left = TreeNode(lst[i])
                q.append(n.left)
            i += 1
            if lst[i] != '#':
                n.right = TreeNode(lst[i])
                q.append(n.right)
            i += 1
        return root

    def _assert(self, root, lst):
        for v in lst:
            assert_equal(root.val, v)
            root = root.right

    def test_simple(self):
        s = Solution()
        root = self._deserialize([0])
        self._assert(s.flatten(root), [0])
        root = self._deserialize([1,2,3,'#','#',4,'#','#',5])
        self._assert(s.flatten(root), [1,2,3,4,5])

    def test_example(self):
        s = Solution()
        root = self._deserialize([1,2,5,3,4,'#',6])
        self._assert(s.flatten(root), [1,2,3,4,5,6])
