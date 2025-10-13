/*
────────────────────────────────────────────
🧠 Day 7 – Q2 | Reverse Nodes in K-Group
Difficulty: Hard
────────────────────────────────────────────

💭 My First Attempt (reverse helper):
────────────────────────────────────────────
I tried to create a separate recursive helper `reverse()` 
that manually controlled reversal, recursion, and connection logic.  
It failed because I:
1. Mixed reversal logic with recursion control (too many pointers)
2. Called recursion before completing my reversal
3. Passed mutated pointers (head/prev1) across recursion frames
4. Accidentally redeclared the function (not called it)

────────────────────────────────────────────
🧠 Intuition Learned:
────────────────────────────────────────────
1️⃣ Each recursion should handle one k-sized segment — nothing more.
2️⃣ Recursion is *delegation*, not cooperation — finish your segment, 
    then hand over control to recursion for the next.
3️⃣ Always return the new head of the reversed section 
    and connect your old head (tail) to recursion result.
4️⃣ Avoid passing shared pointers between recursive calls — 
    every call should start clean.

────────────────────────────────────────────
✅ Correct Intuitive Flow:
────────────────────────────────────────────
reverseKGroup(list, k):
    ├─ check if ≥ k nodes → else return head
    ├─ reverse first k nodes (iteratively)
    ├─ recursion = reverseKGroup(nextSegment, k)
    ├─ head->next = recursion
    └─ return prev (new head of this group)

────────────────────────────────────────────
🔑 Mentor Notes:
────────────────────────────────────────────
✔ Stop “controlling” recursion — trust its return.
✔ Separate reversal (iteration) from recursion (connection).
✔ Don’t pass live pointers that are being reversed.
✔ Recursion is just another iteration tool — 
   use it only to *delegate cleanly*.

────────────────────────────────────────────
*/
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // ✅ Clean version of node count check
    bool checknodes(ListNode* node, int k) {
        int count = 0;
        while (node && count < k) {
            node = node->next;
            count++;
        }
        return count == k;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!checknodes(head, k)) return head;

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* nxt = nullptr;
        int count = 0;

        // Reverse k nodes
        while (curr && count < k) {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
            count++;
        }

        // Recur for remaining nodes
        head->next = reverseKGroup(curr, k);

        // Return new head of this reversed group
        return prev;
    }
};

int main() {
    // Example test case: 1->2->3->4->5, k=2 => 2->1->4->3->5
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(2);
    ListNode* c = new ListNode(3);
    ListNode* d = new ListNode(4);
    ListNode* e = new ListNode(5);
    a->next = b; b->next = c; c->next = d; d->next = e;

    Solution sol;
    ListNode* res = sol.reverseKGroup(a, 2);

    cout << "Reversed in k-groups: ";
    while (res) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << "\n"; // expected: 2 1 4 3 5

    return 0;
}