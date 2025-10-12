/*
────────────────────────────────────────────
🧠 Day 6 – Q3 | Merge Two Sorted Lists
LeetCode: https://leetcode.com/problems/merge-two-sorted-lists/
Difficulty: Easy
Topic: Linked List / Pointers
────────────────────────────────────────────

💭 My Original Attempt:
────────────────────────────────────────────
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* temp1 = list1;
        ListNode* temp2 = list2;
        ListNode* ans = new ListNode();
        ListNode* tempans = ans;
        while(temp1 && temp2){
            if(temp1->val <= temp2->val){
                tempans->val = temp1->val;
                tempans = tempans->next;
                temp1 = temp1->next;
            } else {
                tempans->val = temp2->val;
                tempans = tempans->next;
                temp2 = temp2->next;
            }
        }
        return ans;
    }
};

🧩 Problems Faced:
────────────────────────────────────────────
1. ❌ I assigned values to `tempans->val` instead of connecting nodes.
2. ❌ I moved `tempans = tempans->next` even though `tempans->next` was nullptr.
3. ❌ I never actually created or linked new nodes for the merged list.
4. ❌ I forgot to attach leftover nodes after one list ended.

────────────────────────────────────────────
✅ Correct Approach (Dummy Node Pattern):
────────────────────────────────────────────
1. Create a dummy node and a tail pointer.
2. Attach smaller nodes from list1 or list2 to tail->next.
3. Move the tail forward each time.
4. Once one list ends, attach the remainder of the other.
5. Return dummy->next as the real head of merged list.

────────────────────────────────────────────
🔑 Things to Remember:
────────────────────────────────────────────
• Don’t copy values — **link actual nodes**.
• Dummy node helps avoid head edge cases.
• Always advance `tail` after linking.
• Attach remaining nodes at the end.
• Finally return `dummy->next`, not `dummy`.

────────────────────────────────────────────
📘 Takeaways:
────────────────────────────────────────────
- Linked list problems are about **connections**, not values.
- Dummy + tail pattern is universal for merge-type problems.
- Avoid dereferencing null (`tempans = tempans->next` blindly).
- When stuck, visualize node links like train carriages being attached.

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Create dummy node to start merged list
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;

        // Merge both lists while both are non-empty
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;     // attach smaller node
                list1 = list1->next;    // move in list1
            } else {
                tail->next = list2;     // attach smaller node
                list2 = list2->next;    // move in list2
            }
            tail = tail->next;          // move tail forward
        }

        // Attach any remaining nodes
        if (list1) tail->next = list1;
        if (list2) tail->next = list2;

        // Return merged list (skip dummy head)
        return dummy->next;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example: list1 = 1→2→4, list2 = 1→3→4
    ListNode a1(1), a2(2), a3(4);
    a1.next = &a2; a2.next = &a3;
    ListNode b1(1), b2(3), b3(4);
    b1.next = &b2; b2.next = &b3;

    Solution sol;
    ListNode* merged = sol.mergeTwoLists(&a1, &b1);

    cout << "Merged List: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << "\n"; // expected: 1 1 2 3 4 4

    return 0;
}
