from nose.tools import assert_equal

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param a list of ListNode
    # @return a ListNode
    def mergeKLists(self, lists):
        return self._merge(lists)

    def _merge(self, lists):
        self.heap = []
        for lst in lists:
            if lst:
                self.heap.append(lst)
        if not self.heap: return None
        self._heapify()
        head = ListNode(-1)
        p = head
        while self.heap:
            p.next = self.heap[0]
            p = p.next
            if p.next:
                self.heap[0] = p.next
                self._adjust(0)
            else:
                self.heap[0] = self.heap[-1]
                self.heap.pop()
                self._adjust(0)
        return head.next

    def _heapify(self):
        if not self.heap: return
        ln = len(self.heap)
        for i in range(ln/2)[::-1]:
            self._adjust(i)

    def _adjust(self, i):
        if not self.heap: return
        ln = len(self.heap)
        while i < ln/2:
            left = i+i+1
            right = left+1
            nxt = left
            if right < ln and self.heap[left].val > self.heap[right].val:
                nxt = right
            if self.heap[i].val > self.heap[nxt].val:
                self.heap[i], self.heap[nxt] = \
                    self.heap[nxt], self.heap[i]
            i = nxt


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

    def _traits(self, heap):
        result = [x.val for x in heap]
        return result

    def test_heapify(self):
        s = Solution()
        s.heap = [self._build([x]) for x in [1]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1])
        s.heap = [self._build([x]) for x in [1,2]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,2])
        s.heap = [self._build([x]) for x in [2,1]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,2])
        s.heap = [self._build([x]) for x in [3,2,1]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,2,3])
        s.heap = [self._build([x]) for x in [3,1,2]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,3,2])
        s.heap = [self._build([x]) for x in [2,1,4,3]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,2,4,3])
        s.heap = [self._build([x]) for x in [2,2,2,1]]
        s._heapify()
        assert_equal(self._traits(s.heap), [1,2,2,2])

    def test_simple(self):
        s = Solution()
        lst = []
        lst.append(self._build([]))
        lst.append(self._build([]))
        lst.append(self._build([]))
        assert_equal(self._extract(s.mergeKLists(lst)), [])
        lst = []
        lst.append(self._build([]))
        lst.append(self._build([1,2,3]))
        lst.append(self._build([]))
        assert_equal(self._extract(s.mergeKLists(lst)), [1,2,3])
        lst = []
        lst.append(self._build([1]))
        lst.append(self._build([2]))
        lst.append(self._build([3]))
        assert_equal(self._extract(s.mergeKLists(lst)), [1,2,3])
        lst = []
        lst.append(self._build([1]))
        lst.append(self._build([2,4]))
        lst.append(self._build([3]))
        assert_equal(self._extract(s.mergeKLists(lst)), [1,2,3,4])
        lst = []
        lst.append(self._build([1]))
        lst.append(self._build([2,4,6]))
        lst.append(self._build([3]))
        assert_equal(self._extract(s.mergeKLists(lst)), [1,2,3,4,6])
        lst = []
        lst.append(self._build([1]))
        lst.append(self._build([1,2]))
        lst.append(self._build([1,2,3]))
        lst.append(self._build([1,2,3,4]))
        assert_equal(self._extract(s.mergeKLists(lst)), [1,1,1,1,2,2,2,3,3,4])

    def test_example(self):
        s = Solution()
        lst = []
        lst.append(self._build([-8,-7,-6,-3,-2,-2,0,3]))
        lst.append(self._build([-10,-6,-4,-4,-4,-2,-1,4]))
        lst.append(self._build([-10,-9,-8,-8,-6]))
        lst.append(self._build([-10,0,4]))
        assert_equal(self._extract(s.mergeKLists(lst)), [-10,-10,-10,-9,-8,-8,-8,-7,-6,-6,-6,-4,-4,-4,-3,-2,-2,-2,-1,0,0,3,4,4])
