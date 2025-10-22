/*
📘 Day 10 — Linked List Sorting Deep Dive

-------------------------------------------------------------
🎯 OVERVIEW
-------------------------------------------------------------
This file captures the full intuition and debugging journey
for sorting a linked list — starting from a hand-built in-place
insertion logic to finally reaching the optimal merge sort.

You’ll find:
1️⃣ The thought process behind each approach.
2️⃣ Problems encountered while reasoning it out.
3️⃣ How to fix those problems.
4️⃣ The final working and optimal solutions.

-------------------------------------------------------------
🧠 PART 1: INITIAL INTUITION — INSERTION SORT LOGIC
-------------------------------------------------------------
💡 Intuition:
“I can sort by shifting smaller nodes before bigger ones
as I traverse — just like insertion sort in arrays.”

You tried to move nodes during traversal:
   - Find a smaller node (curr)
   - Move it before min
   - Reconnect pointers

This was conceptually right but failed due to **pointer control**.

⚠️ Problems discovered:
- No control over node before `curr`
- Mutating pointers while traversing same region
- `prev` not reset properly after re-insertion
- `while (temp && temp->next)` skipped last node
- Lost synchronization after swaps

🧩 Corrected Intuition:
Insertion sort works if you always:
   - Detach current node cleanly
   - Find its correct position in sorted part
   - Reinsert it using a `prev` pointer (node before curr)

The breakthrough:
> “You must control the node *before* the one you move.”

That’s what made `prev` (or `beforeCurr`) crucial.

-------------------------------------------------------------
✅ FINAL INSERTION SORT (In-Place O(n²))
-------------------------------------------------------------
*/
struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution_InsertionSort {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* lastSorted = head;
        ListNode* curr = head->next;

        while (curr) {
            if (curr->val >= lastSorted->val) {
                lastSorted = curr;
                curr = curr->next;
            } else {
                ListNode* prev = &dummy;
                while (prev->next->val < curr->val)
                    prev = prev->next;

                lastSorted->next = curr->next;
                curr->next = prev->next;
                prev->next = curr;
                curr = lastSorted->next;
            }
        }

        return dummy.next;
    }
};

/*
🧭 Key takeaways:
- Never rewire inside same traversal path.
- Always detach → find position → reinsert.
- prev and curr control node movement cleanly.
- O(n²) time, but excellent for mastering pointers.
-------------------------------------------------------------
*/


/*
-------------------------------------------------------------
🧠 PART 2: OPTIMAL APPROACH — MERGE SORT (O(n log n))
-------------------------------------------------------------
💡 Intuition:
“I can recursively split the list into halves,
sort each half, and merge them — exactly like merge sort on arrays.”

Why merge sort fits perfectly:
- No need for random access (we just move pointers).
- Merging two sorted lists is linear in time.
- Splitting via slow–fast pointer takes O(n).

The 3 core steps:
1️⃣ Find the middle node.
2️⃣ Split into left and right halves.
3️⃣ Recursively sort + merge.

⚠️ The classic bug:
Initially used:
    fast = head;
    while(fast && fast->next) ...
This made middle point to *right-half* middle for even-sized lists,
causing infinite recursion because one side never shrank properly.

✅ The Fix:
Start fast = head->next,
so `slow` stops *at the node before* mid — true midpoint for split.

-------------------------------------------------------------
✅ FINAL MERGE SORT IMPLEMENTATION (O(n log n))
-------------------------------------------------------------
*/

class Solution_MergeSort {
public:
    ListNode* middle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* mid = middle(head);
        ListNode* left = head;
        ListNode* right = mid->next;
        mid->next = nullptr;

        left = sortList(left);
        right = sortList(right);

        return merge(left, right);
    }
};

/*
-------------------------------------------------------------
🧠 INTUITION DEVELOPMENT — HOW TO THINK LIKE THIS
-------------------------------------------------------------

1️⃣ Understand your constraints
   - Linked list → no random indexing
   - Moving pointers = cheap
   - Swapping values = not always safe

2️⃣ Choose logic that fits the structure
   - Merge sort works naturally with links
   - Insertion sort works naturally with re-linking
   - Quick sort doesn’t (requires random access)

3️⃣ Detect when recursion helps
   - Whenever you can “divide” by slow–fast pointer,
     recursion handles the merging beautifully.

4️⃣ Remember “fast = head->next”
   - This single line ensures your split halves actually shrink.

5️⃣ Recognize merging patterns
   - Merging always ends with: tail->next = l1 ? l1 : l2;
   - Because one side may finish first — attach the rest.

6️⃣ Build habits:
   - Always use dummy nodes to avoid head confusion.
   - Whenever removing/moving a node, track its previous.
   - Never rewire links inside same traversal without resetting pointers.

-------------------------------------------------------------
✅ FINAL TAKEAWAYS
-------------------------------------------------------------
| Pattern        | Concept                        | Complexity |
|----------------|----------------------------------|-------------|
| Insertion Sort | Manual node re-insertion logic   | O(n²)       |
| Merge Sort     | Divide & conquer recursion       | O(n log n)  |
| Key Pointer    | fast = head->next for correct mid|             |
| Common Bug     | Infinite recursion due to overlap|             |
| Must Know      | tail->next = l1 ? l1 : l2        |             |
| Conceptual Win | “Every list problem = pointer ownership” |

-------------------------------------------------------------
🧾 COMMIT MESSAGE
-------------------------------------------------------------
Day 10 — Mastered Linked List Sorting (Insertion + Merge Sort) 🚀
-------------------------------------------------------------
*/
