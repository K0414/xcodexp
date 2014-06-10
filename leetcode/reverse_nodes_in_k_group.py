from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @param k, an integer
    # @return a ListNode
    def reverseKGroup(self, head, k):
        h = head
        n = 0
        while h:
            n += 1
            h = h.next
        nh = head
        ph = None
        loop = n / k
        for i in range(loop):
            t = nh
            h, nh = self._reverse(nh, k)
            if i == 0: head = h
            if ph: ph.next = h
            ph = t
        return head

    def _reverse(self, head, k):
        h = head
        rh = head
        for i in range(k):
            if not rh: return head, None
            rh = rh.next
        for i in range(k):
            h.next, rh = rh, h.next
            h, rh = rh, h
        return rh, h


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

    def _assert(self, h1, h2):
        while h1 and h2:
            assert_equal(h1.val, h2.val)
            h1 = h1.next
            h2 = h2.next
        assert_equal(h1, None)
        assert_equal(h2, None)

    def test_simple(self):
        s = Solution()
        o = []
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 1)), o)
        o = [1]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 1)), o)
        o = [1]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 2)), o)
        o = [1,2]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 1)), o)
        o = [1,2]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 2)), [2,1])
        o = [1,2,3]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 2)), [2,1,3])
        o = [1,2,3,4,5]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 5)), [5,4,3,2,1])

    def test_example(self):
        s = Solution()
        o = [1,2,3,4,5]
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 2)), [2,1,4,3,5])
        assert_equal(self._extract(s.reverseKGroup(self._build(o), 3)), [3,2,1,4,5])
