/*
────────────────────────────────────────────
🚀 Day 8 | Add Two Numbers II (Forward Order)
LeetCode: https://leetcode.com/problems/add-two-numbers-ii/
────────────────────────────────────────────
🧠 Problem:
You’re given two linked lists representing two non-negative integers.
Digits are stored in *forward order* (most significant digit first).
Add the two numbers and return the sum as a linked list.

Example:
  l1 = 7 → 2 → 4 → 3
  l2 = 5 → 6 → 4
Output:
  7 → 8 → 0 → 7
────────────────────────────────────────────
💭 Intuition:
This is the forward-order variant of the earlier Add Two Numbers.

We can’t add directly because the least-significant digits
are at the *end* of the lists.  

To add column-by-column like on paper:
1️⃣ Reverse both lists to make them least-significant-digit first.  
2️⃣ Add normally using carry logic.  
3️⃣ Reverse the result again to restore forward order.

────────────────────────────────────────────
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
    // 🔁 Helper to reverse a linked list
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Step 1: Reverse both lists
        ListNode* Rl1 = reverse(l1);
        ListNode* Rl2 = reverse(l2);

        // Step 2: Add as in reverse-order version
        ListNode dummy(0);
        ListNode* ans = &dummy;
        int carry = 0;

        while (Rl1 || Rl2 || carry) {
            int x = Rl1 ? Rl1->val : 0;
            int y = Rl2 ? Rl2->val : 0;
            int sum = x + y + carry;
            carry = sum / 10;

            ans->next = new ListNode(sum % 10);
            ans = ans->next;

            if (Rl1) Rl1 = Rl1->next;
            if (Rl2) Rl2 = Rl2->next;
        }

        // Step 3: Reverse result to restore forward order
        return reverse(dummy.next);
    }
};
