from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @return a ListNode
    def addTwoNumbers(self, l1, l2):
        return self._add(l1, l2, 0)

    def _add(self, l1, l2, carry):
        n = ListNode(0)
        # Both empty.
        if not l1 and not l2:
            if carry:
                n.val = carry
                return n
            return None
        # Both non-empty.
        if l1 and l2:
            v = l1.val + l2.val + carry
            n.val = v % 10
            n.next = self._add(l1.next, l2.next, v / 10)
            return n
        l = l1 or l2
        # One empty.
        v = l.val + carry
        n.val = v % 10
        n.next = self._add(l.next, None, v / 10)
        return n


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
        l1 = self._build([])
        l2 = self._build([])
        l = self._build([])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([1])
        l2 = self._build([])
        l = self._build([1])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([])
        l2 = self._build([1])
        l = self._build([1])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([1,2])
        l2 = self._build([])
        l = self._build([1,2])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([])
        l2 = self._build([1,2])
        l = self._build([1,2])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([1,2])
        l2 = self._build([1])
        l = self._build([2,2])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([1])
        l2 = self._build([1,2,3,4])
        l = self._build([2,2,3,4])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([9,9,9])
        l2 = self._build([9,9,9])
        l = self._build([8,9,9,1])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([9,9])
        l2 = self._build([9,9,9])
        l = self._build([8,9,0,1])
        self._assert(l, s.addTwoNumbers(l1, l2))
        l1 = self._build([9,9])
        l2 = self._build([9,9,9,9,9])
        l = self._build([8,9,0,0,0,1])
        self._assert(l, s.addTwoNumbers(l1, l2))

    def test_example(self):
        s = Solution()
        l1 = self._build([2,4,3])
        l2 = self._build([5,6,4])
        l = self._build([7,0,8])
        self._assert(l, s.addTwoNumbers(l1, l2))
