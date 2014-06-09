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
    def isValidBST(self, root):
        return self._solve_dfs(root)

    def _solve_dfs(self, root):
        if not root: return True


class TestSolution(object):

    def test_simple(self):
        import __helper
        s = Solution()
        r = __helper.Tree.deserialize([1])
        assert_equal(s.isValidBST(r), True)
        r = __helper.Tree.deserialize([1,2])
        assert_equal(s.isValidBST(r), False)
        r = __helper.Tree.deserialize([1,'#',2])
        assert_equal(s.isValidBST(r), True)

    def test_example(self):
        import __helper
        s = Solution()
        r = __helper.Tree.deserialize([1,2,3,'#',4,5,6])
        assert_equal(s.isValidBST(r), False)
        r = __helper.Tree.deserialize([3,2,4,1,'#','#',6,'#','#',5])
        assert_equal(s.isValidBST(r), True)
        r = __helper.Tree.deserialize([1,1])
        assert_equal(s.isValidBST(r), False)
        r = __helper.Tree.deserialize([10,5,15,'#','#',6,20])
        assert_equal(s.isValidBST(r), False)
