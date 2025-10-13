/*
────────────────────────────────────────────
🧠 Day 7 – Q1 | Reverse Linked List II
LeetCode: https://leetcode.com/problems/reverse-linked-list-ii/
Difficulty: Medium
Topic: Linked List (Partial Reversal)
────────────────────────────────────────────

💭 My Original Attempt:
────────────────────────────────────────────
I tried to find the `left` and `right` nodes using their **values**, 
then reversed the part between them using several pointers (`nxt`, `prev2`, `temp`, `prev3`, etc.).
Finally, I reconnected the reversed section.

However, the logic got tangled and failed in reconnection and traversal.

────────────────────────────────────────────
🔍 Problems in My Approach:
────────────────────────────────────────────
1. ❌ **Confused Values with Positions**
   I compared node->val with `left` and `right`.  
   The problem uses **positions (indices)**, not node values.

2. ❌ **Too Many Pointers Doing the Same Job**
   Overlapping roles like `nxt`, `prev2`, and `temp` made 
   it unclear which pointer tracked what.

3. ❌ **Reversal Loop Used Wrong Pointer Update**
   Inside the reversal, I did `temp = temp->next;` after 
   changing `temp->next`. This caused backward loops.

4. ❌ **Wrong Reconnection**
   I did `prev1->next = nxt`, assuming `nxt` (old left node)
   was the new head of the reversed section.  
   Actually, the node at `right` becomes the new head 
   after reversal.

────────────────────────────────────────────
✅ Correct Intuition (Fixed Approach):
────────────────────────────────────────────
1. Use a **position counter** to reach nodes at `left` and `right`.
2. Keep track of:
   • `prev1` → node before reversal starts.
   • `curr`  → start of reversal (node at position left).
   • `subTail` → start node, becomes the tail after reversal.
3. Reverse exactly (right - left + 1) nodes using
   the standard 3-pointer method (`prev`, `curr`, `nextNode`).
4. Reconnect properly:
   • `prev1->next = prev` (prev is new head of reversed part)
   • `subTail->next = curr` (curr now points to node after right)
5. Handle edge case: if left == 1, update head to new head.

────────────────────────────────────────────
🔑 Professional Notes (To Avoid These Mistakes Next Time):
────────────────────────────────────────────
✔ Always confirm whether `left` and `right` are **indices or values**.
✔ Keep pointer roles distinct and minimal — name them clearly.
✔ Never move to `curr->next` after reassigning `curr->next`.
✔ Visualize reversal as:
   “The node at `left` becomes the tail,
    the node at `right` becomes the head.”
✔ Reconnect start & end carefully: `before->next = newHead`, `tail->next = after`.

────────────────────────────────────────────
📘 Correct Implementation:
────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) return head;

        ListNode* curr = head;
        ListNode* prev1 = nullptr;
        int pos = 1;

        // Step 1: reach node before 'left'
        while (curr && pos < left) {
            prev1 = curr;
            curr = curr->next;
            pos++;
        }

        // Step 2: reverse from left to right
        ListNode* subTail = curr; // original left node
        ListNode* prev = nullptr;
        ListNode* nextNode = nullptr;

        while (curr && pos <= right) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
            pos++;
        }

        // Step 3: reconnect three parts
        if (prev1)
            prev1->next = prev; // connect before reversed part
        else
            head = prev;        // reversed from head

        subTail->next = curr;   // connect tail to remaining list

        return head;
    }
};

int main() {
    // Example: 1->2->3->4->5, left=2, right=4 => 1->4->3->2->5
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b; b.next = &c; c.next = &d; d.next = &e;

    Solution sol;
    ListNode* res = sol.reverseBetween(&a, 2, 4);

    cout << "Reversed List: ";
    while (res) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << "\n"; // expected: 1 4 3 2 5

    return 0;
}
