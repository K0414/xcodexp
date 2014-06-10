from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def insertionSortList(self, head):
        if not head: return head
        if self._sorted(head): return head
        nh = ListNode(0) # Dummy new head.
        h = head
        while h:
            p = nh
            while p.next and p.next.val < h.val:
                p = p.next
            t = h.next
            h.next = p.next
            p.next = h
            h = t
        return nh.next

    def _sorted(self, head):
        while head:
            if head.next and head.val > head.next.val:
                return False
            head = head.next
        return True


import helper
class TestSolution(object):

    def test_simple(self):
        s = Solution()
        l = helper.List.build([1])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1])
        l = helper.List.build([1,2])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2])
        l = helper.List.build([2,1])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2])
        l = helper.List.build([1,2,3])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2,3])
        l = helper.List.build([3,2,1])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2,3])
        l = helper.List.build([3,1,2])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2,3])
        l = helper.List.build([1,3,2])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2,3])
        l = helper.List.build([3,1,1,2])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,1,2,3])
        l = helper.List.build([3,1,2,1])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,1,2,3])
        l = helper.List.build([1,2,3,4,5,6,7])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,2,3,4,5,6,7])

    def test_example(self):
        s = Solution()
        l = helper.List.build([1,1])
        o = s.insertionSortList(l)
        v = helper.List.extract(o)
        assert_equal(v, [1,1])
