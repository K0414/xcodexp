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
        if not root: return True
        #return self._solve_dfs(root, root.val)[2]
        #return self._solve_inorder_traversal(root, None)[1]
        #return self._solve_stack(root)
        #return self._solve_stack2(root)
        return self._solve_iter(root)

    def _solve_dfs(self, root, default):
        if not root:
            return default, default, True
        lmax, lmin, ret = self._solve_dfs(root.left, root.val)
        if not ret:
            return lmax, lmin, False
        rmax, rmin, ret = self._solve_dfs(root.right, root.val)
        if not ret:
            return rmax, rmin, False
        if lmax > root.val or rmin < root.val:
            return root.val, root.val, False
        # Duplicate value should not appear on a BST.
        if root.left and lmax == root.val:
            return rmax, lmin, False
        if root.right and rmin == root.val:
            return rmax, lmin, False
        return rmax, lmin, True

    def _solve_inorder_traversal(self, root, prev):
        if not root:
            return prev, True
        prev, ret = self._solve_inorder_traversal(root.left, prev)
        if not ret:
            return prev, False
        if prev:
            if prev.val >= root.val:
                return prev, False
        return self._solve_inorder_traversal(root.right, root)

    def _solve_stack(self, root):
        stack = [ root ]
        prev = None
        visited = {}
        while stack:
            while stack[-1].left and stack[-1].left not in visited:
                stack.append(stack[-1].left)
            n = stack.pop()
            visited[n] = True
            if prev and prev.val >= n.val:
                return False
            prev = n
            if n.right:
                stack.append(n.right)
        return True

    def _solve_stack2(self, root):
        stack = []
        curr = root
        done = False
        prev = None
        while not done:
            if curr:
                stack.append(curr)
                curr = curr.left
            else:
                if not stack:
                    done = True
                else:
                    curr = stack.pop()
                    if prev and prev.val >= curr.val:
                        return False
                    prev = curr
                    curr = curr.right
        return True

    def _solve_iter(self, root):
        class Iter(object):
            def __init__(self, root):
                self.stack = []
                self.update(root)

            def update(self, root):
                while root:
                    self.stack.append(root)
                    root = root.left

            def next(self):
                if not self.stack: return None
                n = self.stack.pop()
                if n.right:
                    self.update(n.right)
                return n
        it = Iter(root)
        prev = None
        n = it.next()
        while n:
            if prev and prev.val >= n.val:
                return False
            prev = n
            n = it.next()
        return True


class TestSolution(object):

    def test_simple(self):
        import helper
        s = Solution()
        r = helper.Tree.deserialize([1])
        assert_equal(s.isValidBST(r), True)
        r = helper.Tree.deserialize([1,2])
        assert_equal(s.isValidBST(r), False)
        r = helper.Tree.deserialize([1,'#',2])
        assert_equal(s.isValidBST(r), True)

    def test_example(self):
        import helper
        s = Solution()
        r = helper.Tree.deserialize([1,2,3,'#',4,5,6])
        assert_equal(s.isValidBST(r), False)
        r = helper.Tree.deserialize([3,2,4,1,'#','#',6,'#','#',5])
        assert_equal(s.isValidBST(r), True)
        r = helper.Tree.deserialize([1,1])
        assert_equal(s.isValidBST(r), False)
        r = helper.Tree.deserialize([1,'#',1])
        assert_equal(s.isValidBST(r), False)
        r = helper.Tree.deserialize([10,5,15,'#','#',6,20])
        assert_equal(s.isValidBST(r), False)
