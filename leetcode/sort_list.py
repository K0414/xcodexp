from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def sortList(self, head):
        #return self._quicksort(head)
        return self._mergesort(head)

    def _quicksort(self, head):
        if not head or not head.next: return head
        pivot = head
        pre = head
        c = head.next
        n = c
        while n:
            if n.val < pivot.val:
                c.val, n.val = n.val, c.val
                pre = c
                c = c.next
            n = n.next
        pivot.val, pre.val = pre.val, pivot.val
        pre.next = None
        self._quicksort(head)
        pre.next = c
        self._quicksort(c)
        return head

    def _mergesort(self, head):
        if not head or not head.next: return
        fastp = head
        slowp = head
        while fastp.next and fastp.next.next:
            slowp = slowp.next
            fastp = fastp.next.next
        nextp = slowp.next
        slowp.next = None
        h1 = self._mergesort(head)
        h2 = self._mergesort(nextp)
        return self._merge(h1, h2)

    def _merge(self, h1, h2):
        if not h1: return h2
        if not h2: return h1
        if h1.val > h2.val:
            h1, h2 = h2, h1
        head = h1
        while h1 and h2:
            if h1.val < h2.val:
                t = h2
                h2 = h2.next
                t.next = h1.next
                h1.next = h2
                h1 = t.next
            else:

        return h1


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
        result = []
        h = head
        while h:
            result.append(h.val)
            h = h.next
        return result

    def test_simple(self):
        s = Solution()
        assert_equal(self._extract(s.sortList(self._build([]))), [])
        assert_equal(self._extract(s.sortList(self._build([1]))), [1])
        assert_equal(self._extract(s.sortList(self._build([1,2]))), [1,2])
        assert_equal(self._extract(s.sortList(self._build([1,2,3]))), [1,2,3])
        assert_equal(self._extract(s.sortList(self._build([2,1]))), [1,2])
        assert_equal(self._extract(s.sortList(self._build([3,2,1]))), [1,2,3])
        assert_equal(self._extract(s.sortList(self._build([3,1,2]))), [1,2,3])
        assert_equal(self._extract(s.sortList(self._build([2,1,2,1]))), [1,1,2,2])
        assert_equal(self._extract(s.sortList(self._build([1,1,1,1]))), [1,1,1,1])
        assert_equal(self._extract(s.sortList(self._build([1,2,3,2,1]))), [1,1,2,2,3])

    def test_example(self):
        pass

if __name__=='__main__':
    import csv
    l = []
    with open('foo') as f:
        r = csv.reader(f, delimiter=',')
        for row in r:
            l = [ int(x) for x in row ]
    s = Solution()
    ts = TestSolution()
    ll = ts._build(l)
    print ts._extract(s.sortList(ll))
