from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @param x, an integer
    # @return a ListNode
    def partition(self, head, x):
        ghead = ListNode(-1)
        lhead = ListNode(-1)
        n = head
        g = ghead
        l = lhead
        while n:
            if n.val < x:
                l.next = n
                n = n.next
                l = l.next
                l.next = None
            else:
                g.next = n
                n = n.next
                g = g.next
                g.next = None
        l.next = ghead.next
        return lhead.next


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
        l = self._build([])
        self._assert(s.partition(l, 0), self._build([]))
        l = self._build([5])
        self._assert(s.partition(l, 0), self._build([5]))
        l = self._build([5,1])
        self._assert(s.partition(l, 2), self._build([1,5]))

    def test_example(self):
        s = Solution()
        l = self._build([1,4,3,2,5,2])
        self._assert(s.partition(l, 3), self._build([1,2,2,4,3,5]))
