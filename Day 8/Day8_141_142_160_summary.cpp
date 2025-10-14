/*
────────────────────────────────────────────
🚀 Day 8 | Linked List Pointer Geometry Summary
────────────────────────────────────────────
Problems Covered:
• 141. Linked List Cycle
• 142. Linked List Cycle II
• 160. Intersection of Two Linked Lists

────────────────────────────────────────────
🧠 Core Theme:
"Two pointers — one faster, one slower — reveal the hidden structure of the list."

We use this pointer geometry to detect:
1️⃣ Existence of a cycle
2️⃣ Entry point of a cycle
3️⃣ Intersection point of two separate lists
────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

/*────────────────────────────────────────────
141. LINKED LIST CYCLE
────────────────────────────────────────────
💭 Intuition:
- Two runners on a circular track (slow = 1x, fast = 2x).
- If there’s no loop → fast hits nullptr.
- If there’s a loop → fast laps slow ⇒ they meet inside the cycle.

⚙️ Logic:
- Move slow by one, fast by two.
- If (slow == fast) ⇒ cycle exists.
────────────────────────────────────────────
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
bool hasCycle(ListNode* head) {
    if (!head) return false;
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

/*────────────────────────────────────────────
142. LINKED LIST CYCLE II
────────────────────────────────────────────
💭 Intuition:
When slow & fast meet inside the loop:
Let:
  L1 = distance from head → cycle start
  L2 = distance from start → meeting point
  C  = length of cycle

Then:
  Distance(fast) = L1 + L2 + nC
  Distance(slow) = L1 + L2
  Since fast moves twice as fast:
    L1 + L2 + nC = 2(L1 + L2)
  → L1 = nC - L2
Thus, if one pointer starts at head (L1) 
and another starts at meeting point (C - L2), 
they meet at the cycle start.

⚙️ Logic:
1. Detect meeting using Floyd’s cycle check.
2. Move one pointer to head, both one step at a time.
3. The node they meet at = start of cycle.
────────────────────────────────────────────
*/
ListNode* detectCycle(ListNode* head) {
    if (!head) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;

    // Step 1: Detect cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (!fast || !fast->next) return nullptr; // no cycle

    // Step 2: Find entry point
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow; // start of cycle
}

/*────────────────────────────────────────────
160. INTERSECTION OF TWO LINKED LISTS
────────────────────────────────────────────
💭 Intuition:
Let:
  A length = a + c
  B length = b + c
(c = shared intersection length)

If you move pointers normally, one list ends before the other.
But if each pointer switches head after finishing its list,
they both travel:
  a + c + b  =  b + c + a

💡 Same total distance ⇒ they meet at intersection (if any).

⚙️ Logic:
- Traverse both simultaneously.
- If one ends, redirect it to other’s head.
- When they meet, return that node.
────────────────────────────────────────────
*/
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;

    ListNode* a = headA;
    ListNode* b = headB;

    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }

    return a; // nullptr (no intersection) or intersection node
}

/*────────────────────────────────────────────
🔑 PATTERN SUMMARY
────────────────────────────────────────────
FLOYD’S POINTER GEOMETRY TEMPLATE:
-----------------------------------
1️⃣  (Cycle Detection)
    slow = head
    fast = head
    while (fast && fast->next)
        slow = slow->next
        fast = fast->next->next

2️⃣  (Cycle Start)
    slow = head
    while (slow != fast)
        slow = slow->next
        fast = fast->next

3️⃣  (Intersection)
    while (a != b)
        a = (a) ? a->next : headB
        b = (b) ? b->next : headA

────────────────────────────────────────────
📈 Time Complexity:
All three → O(n)
🧮 Space Complexity:
All three → O(1)

────────────────────────────────────────────
🧭 Key Takeaways:
• “Two speeds” reveal geometry of cycles.
• “Equalizing paths” reveals intersections.
• No extra data structures needed.
• Same logic extends to array and graph cycle detection too.

────────────────────────────────────────────
*/
