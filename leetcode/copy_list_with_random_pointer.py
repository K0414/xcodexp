from nose.tools import assert_equal, assert_is_not

# Definition for singly-linked list with a random pointer.
class RandomListNode:
    def __init__(self, x):
        self.label = x
        self.next = None
        self.random = None

class Solution:
    # @param head, a RandomListNode
    # @return a RandomListNode
    def copyRandomList(self, head):
        #return self._copy(head)
        return self._copy_inplace(head)

    def _copy(self, head):
        if not head: return None
        nodes = []
        idxmap = {}
        h = head
        while h:
            idxmap[h] = len(idxmap)
            nodes.append(RandomListNode(h.label))
            h = h.next
        nodes.append(None)
        h = head
        for i in range(len(idxmap)):
            nodes[i].next = nodes[i+1]
            if h.random:
                nodes[i].random = nodes[idxmap[h.random]]
            h = h.next
        return nodes[0]

    def _copy_inplace(self, head):
        if not head: return None
        # 1) Copy.
        h = head
        while h:
            n = RandomListNode(h.label)
            n.next = h.next
            h.next = n
            h = n.next
        # 2) Connect random.
        h = head
        while h:
            n = h.next
            if h.random:
                n.random = h.random.next
            h = n.next
        # 3) Split.
        newh = head.next
        h = head
        p = newh
        while h:
            h.next = p.next
            h = h.next
            if h:
                p.next = h.next
                p = p.next
        return newh


class TestSolution(object):

    def _build(self, L):
        from random import choice
        if not L: return None
        nodes = []
        for v in L:
            nodes.append(RandomListNode(v))
        nodes.append(None)
        for i in range(len(L)):
            nodes[i].next = nodes[i+1]
            nodes[i].random = choice(nodes)
        return nodes[0]

    def _assert(self, h1, h2):
        while h1 and h2:
            assert_is_not(h1, h2)
            assert_equal(h1.label, h2.label)
            if h1.random:
                assert_is_not(h1.random, h2.random)
                assert_equal(h1.random.label, h2.random.label)
            h1 = h1.next
            h2 = h2.next
        print h1
        print h2
        assert_equal(h1, None)
        assert_equal(h2, None)

    def test_simple(self):
        s = Solution()
        l1 = self._build([9,9,9,9,9])
        l2 = s.copyRandomList(l1)
        self._assert(l1, l2)

    def test_example(self):
        s = Solution()
        l1 = self._build([2,4,3])
        l2 = s.copyRandomList(l1)
        self._assert(l1, l2)
        l1 = self._build([5,6,4])
        l2 = s.copyRandomList(l1)
        self._assert(l1, l2)
        l1 = self._build([7,0,8])
        l2 = s.copyRandomList(l1)
        self._assert(l1, l2)
