// 🔗 Problem: https://leetcode.com/problems/merge-k-sorted-lists/
// 🎯 Topic: Linked List — Divide & Conquer, Recursion, Iterative Merging

/*
🧠 INTUITION:
We’re given 'k' sorted linked lists. We must merge them into one sorted list.

We already know how to merge two sorted linked lists (like in Merge Sort).
Now, we extend that to 'k' lists — multiple ways to think:

----------------------------------------------------------
1️⃣ Sequential Merge (Naive)
----------------------------------------------------------
- Merge one list with the next repeatedly.
- Simple but inefficient: O(k * N) time (each merge grows in size).
- Works fine for small 'k' (like the Flatten Linked List problem).

----------------------------------------------------------
2️⃣ Divide & Conquer (Recursive)
----------------------------------------------------------
- Same idea as Merge Sort.
- Split the vector into two halves, merge each half recursively,
  then merge the two results.

    Time Complexity: O(N log k)
    Space Complexity: O(log k) recursion stack
    Elegant, balanced, and scalable.

----------------------------------------------------------
3️⃣ Iterative Two-Pointer (Low–High Collapse)
----------------------------------------------------------
- Avoid recursion.
- Merge lists in pairs from both ends (low, high) → shrink inward.
- After each round, number of lists halves automatically.
- No explicit mid variable, pointers self-adjust via high-- in loop.

    Time Complexity: O(N log k)
    Space Complexity: O(1)
    Best iterative alternative to recursion.

Both (2) and (3) achieve optimal complexity.
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------
// 🔧 Merge Two Sorted Lists
// -------------------------

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* merge(ListNode* a, ListNode* b) {
    if (!a) return b;
    if (!b) return a;

    ListNode dummy;          // dummy starter node
    ListNode* tail = &dummy; // tail pointer for merged list

    while (a && b) {
        if (a->val < b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    tail->next = (a ? a : b); // attach remaining nodes
    return dummy.next;
}

// ----------------------------------------------------------
// ⚙️ 1. RECURSIVE DIVIDE & CONQUER APPROACH (split by mid)
// ----------------------------------------------------------
class SolutionRecursive {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0) return nullptr;
        return mergeDivide(lists, 0, n - 1);
    }

private:
    ListNode* mergeDivide(vector<ListNode*>& lists, int left, int right) {
        if (left == right) return lists[left];
        int mid = left + (right - left) / 2;
        ListNode* l1 = mergeDivide(lists, left, mid);
        ListNode* l2 = mergeDivide(lists, mid + 1, right);
        return merge(l1, l2);
    }
};

/*
🧩 DRY RUN (Recursive)
Input: 4 lists → [L1, L2, L3, L4]
Round 1: merge(L1, L2) and merge(L3, L4)
Round 2: merge(result1, result2)
Output: Fully merged sorted list

🕒 Complexity: O(N log k)
🧮 Space: O(log k) recursion
*/

// ----------------------------------------------------------
// ⚙️ 2. ITERATIVE LOW–HIGH COLLAPSING APPROACH
// ----------------------------------------------------------
class SolutionIterative {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0) return nullptr;

        int low = 0;
        int high = n - 1;

        // Keep merging until one list remains
        while (high != 0) {
            low = 0;

            while (low < high) {
                lists[low] = merge(lists[low], lists[high]);
                low++;
                high--;
            }

            // After this loop, 'high' naturally lands on new last index
            // No explicit mid or end variable needed
            // Example:
            // For n=5 → merges: (0,4), (1,3) → high=2
            // Next round: (0,2) → high=1 → (0,1) → done ✅
        }

        return lists[0];
    }
};

/*
🧩 WHY THIS WORKS:
- Each round merges pairs (low, high) and shrinks range automatically.
- 'high' self-adjusts after all pair merges.
- No need for extra variable (like end or mid) — pointer math balances itself.

✅ Handles even/odd list counts cleanly.
✅ Equivalent to recursive divide & conquer, but purely iterative.

🕒 Complexity: O(N log k)
🧮 Space: O(1)
*/

// ----------------------------------------------------------
// 🔍 COMPARISON
// ----------------------------------------------------------
/*
| Approach            | Recursion? | Complexity | Space | Notes |
|---------------------|------------|-------------|--------|-------|
| Sequential Merge    | No         | O(k * N)    | O(1)   | Easy but slow |
| Divide & Conquer    | Yes        | O(N log k)  | O(log k) | Clean logic |
| Iterative Collapse  | No         | O(N log k)  | O(1)   | Fast + Stack Safe |

🧠 INTUITION RECAP:
- Flatten → Sequential Merge (small k, linear)
- Merge K Lists → Divide & Conquer / Iterative Pairing (large k)
- Heap (Priority Queue) → if we need "next smallest" dynamically
*/

// ----------------------------------------------------------
// ✅ LEARNINGS
// ----------------------------------------------------------
/*
1️⃣ Recursion vs Iteration — Two sides of the same logic.
   Recursion divides automatically; iteration divides manually (low–high).

2️⃣ When merging many lists, merging sequentially grows in cost each step.
   → Use divide & conquer to balance workload.

3️⃣ Pointer patterns (like high--, low++) can replace explicit mid math.

4️⃣ Dummy nodes are your best friend when building linked structures.

5️⃣ Always analyze *merge growth*: 
   - If cost grows cumulatively → use divide & conquer.
   - If cost remains constant → sequential merging is fine.
*/

// ----------------------------------------------------------
// 🧾 COMMIT MESSAGE
// ----------------------------------------------------------
/*
Day 9 — Merged K Sorted Lists using Recursive Divide & Conquer 
and Optimized Iterative Low–High Pairing 🚀
*/
