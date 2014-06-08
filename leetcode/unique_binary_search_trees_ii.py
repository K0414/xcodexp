from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @return a list of tree node
    def generateTrees(self, n):
        return self._solve(n)

    def _solve(self, n):
        if n <= 0: return None
        nodes = [ TreeNode(1) ]
        for i in range(1, n):
            ln = len(nodes)
            for j in range(ln):
                nodes.append(TreeNode(i+1))
                nodes[-1].left = copy(nodes[j])
            for j in range(ln):
                p = nodes[j]
                while p.right:
                    p = p.right
                p.right = TreeNode(i+1))
            ...
        return result

    def _copy(self, root):
        if not root: return None
        cp = TreeNode(root.val)
        cp.left = self._copy(root.left)
        cp.right = self._copy(root.right)
        return cp


class TestSolution(object):

    def _serialize(self, root):
        ...

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

    def _assert(self):
        pass

    def test_copy(self):
        pass

    def test_example(self):
        s = Solution()
        trees = s.generateTrees(3)

