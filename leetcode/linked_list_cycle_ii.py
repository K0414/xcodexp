from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a list node
    def detectCycle(self, head):
        #return self._detect_cut(head)
        return self._detect_count(head)

    def _detect_count(self, head):
        n = head
        n2 = head
        while n2:
            n = n.next
            n2 = n2.next
            if not n2:
                return None
            n2 = n2.next
            if n == n2: # meet.
                n2 = head
                while n != n2:
                    n = n.next
                    n2 = n2.next
                return n
        return None

    def _detect_cut(self, head):
        n = head
        n2 = head
        while n2:
            n = n.next
            n2 = n2.next
            if not n2:
                return None
            n2 = n2.next
            if n == n2: # meet.
                h = head
                h2 = n.next
                n.next = None
                l = self._len(head)
                l2 = self._len(h2)
                if l < l2:
                    h2 = self._step(h2, l2-l)
                else:
                    h = self._step(head, l-l2)
                while h != h2:
                    h = h.next
                    h2 = h2.next
                return h
        return None

    def _len(self, head):
        l = 0
        h = head
        while h:
            l += 1
            h = h.next
        return l

    def _step(self, head, count):
        h = head
        for i in range(count):
            h = h.next
            if not h:
                return None
        return h


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
        assert_equal(s.detectCycle(h), h)
        h = self._build([0,0,0,0,0,0,0,0,0])
        assert_equal(s.detectCycle(h), None)
        h.next.next = h.next
        assert_equal(s.detectCycle(h), h.next)

    def test_example(self):
        pass
