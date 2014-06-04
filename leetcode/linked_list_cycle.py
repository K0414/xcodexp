from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a boolean
    def hasCycle(self, head):
        fastp = head
        slowp = head
        while fastp and fastp.next:
            slowp = slowp.next
            fastp = fastp.next.next
            if fastp == slowp:
                return True
        return False


class TestSolution(object):

    def _build(self, L):
        if not L: return None
        head = ListNode(L[0])
        curr = head
        for v in L[1:]:
            curr.next = ListNode(v)
            curr = curr.next
        return head

    def test_simple(self):
        s = Solution()
        h = self._build([0])
        h.next = h
        assert_equal(s.hasCycle(h), True)
        h = self._build([0,0,0,0,0,0,0,0,0])
        assert_equal(s.hasCycle(h), False)
        h.next.next = h.next
        assert_equal(s.hasCycle(h), True)

    def test_example(self):
        pass
