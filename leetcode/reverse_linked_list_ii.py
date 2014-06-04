from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @param m, an integer
    # @param n, an integer
    # @return a ListNode
    def reverseBetween(self, head, m, n):
        if not head: return head
        if m == n: return head
        pre = None
        p = head
        for i in range(1, m):
            pre = p
            p = p.next
            if not p:
                return None
        pstart = pre
        for i in range(m, n+1):
            pre, p.next = p.next, pre
            pre, p = p, pre
        if pstart:
            pstart.next.next = p
            pstart.next = pre
        else:
            head.next = p
            head = pre
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

    def _extract(self, head):
        res = []
        while head:
            res.append(head.val)
            head = head.next
        return res

    def test_simple(self):
        s = Solution()
        l = self._build([1])
        r = s.reverseBetween(l, 1, 1)
        assert_equal([1], self._extract(r))
        l = self._build([1,2])
        r = s.reverseBetween(l, 1, 1)
        assert_equal([1,2], self._extract(r))
        l = self._build([1,2])
        r = s.reverseBetween(l, 1, 2)
        assert_equal([2,1], self._extract(r))
        l = self._build([1,2])
        r = s.reverseBetween(l, 2, 2)
        assert_equal([1,2], self._extract(r))
        l = self._build([1,2,3])
        r = s.reverseBetween(l, 1, 3)
        assert_equal([3,2,1], self._extract(r))
        l = self._build([1,2,3,4])
        r = s.reverseBetween(l, 2, 3)
        assert_equal([1,3,2,4], self._extract(r))
        l = self._build([1,2,3,4,5,6,7])
        r = s.reverseBetween(l, 4, 4)
        assert_equal([1,2,3,4,5,6,7], self._extract(r))

    def test_example(self):
        s = Solution()
