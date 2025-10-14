/*
────────────────────────────────────────────
🚀 Day 8 | Add Two Numbers (Linked List Arithmetic)
LeetCode: https://leetcode.com/problems/add-two-numbers/
────────────────────────────────────────────
🧠 Topic: Linked List arithmetic, digit-by-digit addition, carry handling.
────────────────────────────────────────────

👣 This file contains:
1️⃣ My first incorrect approach (reverse + addition)
2️⃣ My second almost-correct approach (loop-based with carry)
3️⃣ The final correct and optimal version
────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

/*────────────────────────────────────────────
1️⃣ FIRST ATTEMPT — Reverse + Add
────────────────────────────────────────────
🧩 What I Tried:
I wrote a helper `reverse()` to reverse both lists,
then tried to add them node by node.

💥 What Went Wrong:
• I reversed the lists unnecessarily — in this problem,
  numbers are already stored in *reverse order*.
• My reverse function had wrong loop condition (`curr && curr->next`)
  → It skipped the last node and returned the wrong pointer.
• I didn’t handle carry.
• I stopped loop using `(Rl1 && Rl2)` instead of `(Rl1 || Rl2)`.
• Result pointer was being modified directly → lost head reference.
────────────────────────────────────────────
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class WrongAttempt_ReverseAdd {
public:
    // ❌ Buggy reverse — misses last node and returns nullptr
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->next) { // should be while(curr)
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return curr; // should return prev
    }

    // ❌ Wrong loop condition & logic
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* Rl1 = reverse(l1);
        ListNode* Rl2 = reverse(l2);
        ListNode* ans = new ListNode();
        while ((Rl1 && Rl1->next) && (Rl2 && Rl2->next)) { // should be (Rl1 || Rl2)
            int sum = Rl1->val + Rl2->val;
            ans->val = sum;
            Rl1 = Rl1->next;
            Rl2 = Rl2->next;
            ans->next = new ListNode();
            ans = ans->next;
        }
        return ans; // lost reference to start
    }
};

/*
────────────────────────────────────────────
💭 MENTOR NOTES – HOW TO IMPROVE INTUITION:
────────────────────────────────────────────
✔ Understand the problem’s number representation.
   → LeetCode 2 already stores digits in reverse order.
✔ Reverse is only needed in LeetCode 445 (Add Two Numbers II).
✔ Separate concerns: reversal vs. addition.
✔ Always keep a pointer to head when creating a new list.
────────────────────────────────────────────
*/


/*────────────────────────────────────────────
2️⃣ SECOND ATTEMPT — Carry Handling (Almost Correct)
────────────────────────────────────────────
🧩 What I Did Right:
• Used `while(l1 || l2 || carry)` — perfect stopping condition.
• Used ternary checks for safe traversal.
• Implemented carry = sum / 10.

💥 What Went Wrong:
• Created an empty new node unconditionally after each iteration.
  → Added an extra blank node at the end.
• Didn’t handle final carry cleanly.
• Returned `head` (with extra dummy) instead of `head->next`.
────────────────────────────────────────────
*/

class Attempt_LoopCarry {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans = new ListNode();
        ListNode* head = ans;
        int carry = 0;
        while (l1 || l2 || carry) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = x + y + carry;
            carry = sum / 10;

            ans->val = sum % 10;
            ans->next = new ListNode(); // ❌ creates extra node
            ans = ans->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        return head; // ❌ returns dummy + extra empty node
    }
};

/*
────────────────────────────────────────────
💭 MENTOR NOTES – IMPROVE INTUITION:
────────────────────────────────────────────
✔ Never unconditionally create the next node.
   → Only when there’s another digit to process.
✔ Use a dummy node pattern (tail-based addition).
✔ Always return dummy->next.
✔ Think in terms of *column-wise addition* like on paper:
     sum = x + y + carry;
     carry = sum / 10;
     digit = sum % 10;
────────────────────────────────────────────
*/


/*────────────────────────────────────────────
3️⃣ FINAL VERSION — Clean, Correct, Elegant
────────────────────────────────────────────
💎 What’s Perfected Here:
✔ Dummy node for easy construction.
✔ Handles carry correctly.
✔ Avoids unnecessary reversal.
✔ Uses standard add-carry formula.
────────────────────────────────────────────
*/

class Final_AddTwoNumbers {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);        // dummy node simplifies logic
        ListNode* tail = &dummy;  // pointer to build result
        int carry = 0;

        while (l1 || l2 || carry) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = x + y + carry;

            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        return dummy.next; // skip dummy node
    }
};

/*
────────────────────────────────────────────
🧠 FINAL INTUITION – HOW TO THINK IN INTERVIEWS
────────────────────────────────────────────
Imagine adding numbers column by column:
  342
+ 465
------
  807

→ Each node represents a digit.
→ Add corresponding digits + carry.
→ Store remainder, carry over.
→ Keep looping till carry is gone.

🔑 THINKING FRAMEWORK:
1️⃣ Use dummy node for result head.
2️⃣ Use carry = sum / base.
3️⃣ Use digit = sum % base.
4️⃣ Move both pointers if they exist.
5️⃣ Return dummy->next.

📈 Time Complexity: O(max(n, m))
🧮 Space Complexity: O(1) (output list excluded)
────────────────────────────────────────────
✅ Key Takeaways:
• Reverse is only needed in forward-order problems (LeetCode 445).
• Always use dummy node to simplify new list construction.
• “Carry logic” is universal — base 10 for decimal, base 2 for binary.
• Never lose track of result head pointer.
────────────────────────────────────────────
*/
