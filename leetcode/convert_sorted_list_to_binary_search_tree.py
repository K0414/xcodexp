from nose.tools import assert_equal

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a list node
    # @return a tree node
    def sortedListToBST(self, head):
        return self._convert(head)

    def _convert(self, head):
        if not head: return None
        prev = None
        slow = head
        fast = head
        while fast and fast.next:
            prev = slow
            slow = slow.next
            fast = fast.next.next
        root = TreeNode(slow.val)
        root.right = self._convert(slow.next)
        if prev:
            prev.next = None
            root.left = self._convert(head)
        return root

import helper
class TestSolution(object):

    def tets_simple(self):
        s = Solution()
        head = helper.List.build([1])
        root = s.sortedListToBST(head)
        res = helper.Tree.serialize(root)
        assert_equal(res, [1])

    def test_example(self):
        s = Solution()
        head = helper.List.build([1,2,3,4,5,6,7])
        root = s.sortedListToBST(head)
        res = helper.Tree.serialize(root)
        assert_equal(res, [4, 2, 6, 1, 3, 5, 7])
