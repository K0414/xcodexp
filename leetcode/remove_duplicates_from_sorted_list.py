from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def deleteDuplicates(self, head):
        curr = head
        while curr:
            while curr.next and (curr.next.val == curr.val):
                curr.next = curr.next.next
            curr = curr.next
        return head


class TestSolution(object):

    def _build(self, L):
        if not L: return None
        head = ListNode(L[0])
        curr = head
        for v in L[1:]:
            curr.next = ListNode(v)
            curr = curr.next
        return head

    def _assert(self, h1, h2):
        while h1 and h2:
            assert_equal(h1.val, h2.val)
            h1 = h1.next
            h2 = h2.next
        assert_equal(h1, None)
        assert_equal(h2, None)

    def test_simple(self):
        s = Solution()
        l = s.deleteDuplicates(self._build([]))
        self._assert(l, None)
        l = s.deleteDuplicates(self._build([1]))
        self._assert(l, self._build([1]))
        l = s.deleteDuplicates(self._build([1,2]))
        self._assert(l, self._build([1,2]))
        l = s.deleteDuplicates(self._build([1,2,3]))
        self._assert(l, self._build([1,2,3]))
        l = s.deleteDuplicates(self._build([1,1,1,1,1]))
        self._assert(l, self._build([1]))
        l = s.deleteDuplicates(self._build([1,2,2,2,2]))
        self._assert(l, self._build([1,2]))
        l = s.deleteDuplicates(self._build([1,2,2,2,3]))
        self._assert(l, self._build([1,2,3]))
        l = s.deleteDuplicates(self._build([1,2,2,2,3,3]))
        self._assert(l, self._build([1,2,3]))



    def test_example(self):
        s = Solution()
        l = s.deleteDuplicates(self._build([1,1,2]))
        self._assert(l, self._build([1,2]))
        l = s.deleteDuplicates(self._build([1,1,2,3,3]))
        self._assert(l, self._build([1,2,3]))
