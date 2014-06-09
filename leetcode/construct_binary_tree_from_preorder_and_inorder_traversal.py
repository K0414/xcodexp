from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param preorder, a list of integers
    # @param inorder, a list of integers
    # @return a tree node
    def buildTree(self, preorder, inorder):
        return self._solve(preorder, inorder)

    def _solve(self, preorder, inorder):
        if not preorder or not inorder:
            return None
        r = preorder[0]
        idx = -1
        for i, v in enumerate(inorder):
            if r == v:
                idx = i
                break
        if idx == -1:
            return None
        root = TreeNode(r)
        root.left = self._solve(preorder[1:idx+1], inorder[:idx])
        root.right = self._solve(preorder[idx+1:], inorder[idx+1:])
        return root


import helper
class TestSolution(object):
    def test_simple(self):
        s = Solution()
        root = s.buildTree([1], [1])
        assert_equal(helper.Tree.serialize(root), [1])
        root = s.buildTree([1,2], [1,2])
        assert_equal(helper.Tree.serialize(root), [1, '#', 2])
        root = s.buildTree([1,2], [2,1])
        assert_equal(helper.Tree.serialize(root), [1, 2])

    def test_example(self):
        s = Solution()
        root = s.buildTree([1,2,4,3,5,6], [2,4,1,5,3,6])
        assert_equal(helper.Tree.serialize(root), [1,2,3,'#',4,5,6])
