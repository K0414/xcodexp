#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode *head) {
        ListNode *tail;
        tail = split(head);
        tail = reverse(tail);
        merge(head, tail);
    }

private:
    ListNode *split(ListNode *head) {
        if (head == NULL)
            return NULL;

        ListNode *fast, *slow;
        fast = slow = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *ret = slow->next;
        slow->next = NULL;
        return ret;
    }

    ListNode *reverse(ListNode *head) {
        if (head == NULL)
            return NULL;

        ListNode *h, *rh, *t;
        h = head;
        rh = NULL;
        while (h) {
            // 1) swap(rh, h->next);
            t = rh; rh = h->next; h->next = t;
            // 2) swap(rh, h);
            t = h; h = rh; rh = t;
        }
        return rh;
    }

    void merge(ListNode *h1, ListNode *h2) {
        ListNode *t;
        while (h1 && h2) {
            t = h2->next;
            h2->next = h1->next;
            h1->next = h2;
            h1 = h2->next;
            h2 = t;
        }
        if (h2) h1->next = h2;
    }
};

ListNode *build(int n)
{
    if (n <= 0) return NULL;

    ListNode *p = (ListNode *)malloc(n * sizeof(ListNode));
    for (int i = 0; i < n; i++) {
        p[i].val = (i+1);
        p[i].next = (i == n-1) ? NULL : &p[i+1];
    }
    return p;
}

void print(ListNode *head)
{
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void test(int n)
{
    Solution s;
    ListNode *list;

    list = build(n);
    cout << "original:\t";
    print(list);
    s.reorderList(list);
    cout << "reordered:\t";
    print(list);
    free(list);
}

int main()
{
    test(0);
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    test(6);
    
    return 0;
}
