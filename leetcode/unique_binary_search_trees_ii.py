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
        # nodes[len][i] contains all binary trees
        # with nodes from 1 to len and root i.
        nodes = [ [None] ]
        for i in range(1, n):
            nodes.append([])
            for j in range(i):
                ln = len(nodes[j])
                for k in range(ln):
                    node = TreeNode(i)
                    node.left = self._copy(nodes[j][k])
                    nodes[-1].append(node)
        return nodes

    def _copy(self, root):
        if not root: return None
        cp = TreeNode(root.val)
        cp.left = self._copy(root.left)
        cp.right = self._copy(root.right)
        return cp


class TestSolution(object):

    def _assert(self):
        pass

    def test_copy(self):
        pass

    def test_example(self):
        s = Solution()
        trees = s.generateTrees(3)


