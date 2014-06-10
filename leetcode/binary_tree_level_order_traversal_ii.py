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
    def levelOrderBottom(self, root):
        #return self._solve_reverse(root)
        return self._solve_dfs(root)

    def _solve_reverse(self, root):
        if not root: return []
        result = []
        q = [root]
        while q:
            result.append([x.val for x in q])
            for i in range(len(q)):
                n = q.pop(0)
                if n.left:
                    q.append(n.left)
                if n.right:
                    q.append(n.right)
        result.reverse()
        return result

    def _solve_dfs(self, root):
        if not root: return []
        self.result = []
        self._dfs(root, 0)
        return self.result

    def _dfs(self, root, level):
        if not root: return
        if level >= len(self.result):
            self.result.insert(0, [])
        self._dfs(root.left, level+1)
        self._dfs(root.right, level+1)
        self.result[-level-1].append(root.val)


class TestSolution(object):

    def test_simple(self):
        s = Solution()

    def test_example(self):
        import helper
        s = Solution()
        root = helper.Tree.deserialize([3,9,20,'#','#',15,7])
        assert_equal(s.levelOrderBottom(root), [[15,7],[9,20],[3]])
