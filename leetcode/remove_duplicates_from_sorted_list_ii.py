from nose.tools import assert_equal
from .helper import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def deleteDuplicates(self, head):
        prev = None
        curr = head
        while curr:
            if curr.next and curr.next.val == curr.val:
                while curr.next and curr.next.val == curr.val:
                    curr.next = curr.next.next
                if prev:
                    prev.next = curr.next
                else:
                    head = curr.next
            else:
                prev = curr
            curr = curr.next
        return head


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        h = List.build([])
        r = s.deleteDuplicates(h)
        assert_equal(List.extract(r), [])

    def test_example(self):
        s = Solution()
        h = List.build([1,2,3,3,4,4,5])
        r = s.deleteDuplicates(h)
        assert_equal(List.extract(r), [1,2,5])
        h = List.build([1,1,1,2,3])
        r = s.deleteDuplicates(h)
        assert_equal(List.extract(r), [2,3])

