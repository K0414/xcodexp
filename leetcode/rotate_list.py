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
    def rotateRight(self, head, k):
        if not head: return head
        ln = 0
        h = head
        tail = head
        while h:
            ln += 1
            tail = h
            h = h.next
        k %= ln
        if not k:
            return head
        tail.next = head
        h = head
        for i in range(ln-k-1):
            h = h.next
        head = h.next
        h.next = None
        return head


class TestSolution(object):

    def test_simple(self):
        import helper
        s = Solution()
        h = helper.List.build([])
        h = s.rotateRight(h, 0)
        assert_equal(helper.List.extract(h), [])
        h = helper.List.build([])
        h = s.rotateRight(h, 1)
        assert_equal(helper.List.extract(h), [])
        h = helper.List.build([1])
        h = s.rotateRight(h, 0)
        assert_equal(helper.List.extract(h), [1])
        h = helper.List.build([1])
        h = s.rotateRight(h, 10)
        assert_equal(helper.List.extract(h), [1])
        h = helper.List.build([1,2])
        h = s.rotateRight(h, 0)
        assert_equal(helper.List.extract(h), [1,2])
        h = helper.List.build([1,2])
        h = s.rotateRight(h, 1)
        assert_equal(helper.List.extract(h), [2,1])
        h = helper.List.build([1,2])
        h = s.rotateRight(h, 2)
        assert_equal(helper.List.extract(h), [1,2])
        h = helper.List.build([1,2])
        h = s.rotateRight(h, 3)
        assert_equal(helper.List.extract(h), [2,1])

    def test_example(self):
        import helper
        s = Solution()
        h = helper.List.build([1,2,3,4,5])
        h = s.rotateRight(h, 2)
        assert_equal(helper.List.extract(h), [4,5,1,2,3])
        h = helper.List.build([1,2,3,4,5])
        h = s.rotateRight(h, 7)
        assert_equal(helper.List.extract(h), [4,5,1,2,3])
