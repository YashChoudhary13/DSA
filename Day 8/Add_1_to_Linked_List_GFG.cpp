/*
────────────────────────────────────────────
🚀 Problem: Add 1 to a Number Represented as Linked List
Platform: GeeksForGeeks
Link: https://www.geeksforgeeks.org/add-1-number-represented-linked-list/
────────────────────────────────────────────
🧠 Problem Statement:
Given a number represented as a linked list, where each node
contains a single digit and the digits are stored in forward order,
add 1 to the number and return the resulting list.

Example:
Input:  1 → 9 → 9 → 9
Output: 2 → 0 → 0 → 0

────────────────────────────────────────────
💭 Intuition:
The least significant digit is at the *end* of the linked list,
so adding 1 directly from the tail is difficult.

To simplify:
1️⃣ Reverse the list (so we can start from least significant digit)
2️⃣ Add 1 while maintaining carry
3️⃣ If a carry remains after the last node, append a new node
4️⃣ Reverse again to restore the original order

────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
  public:
    // 🔁 Step 1: Reverse helper function
    Node* reverse(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        Node* nxt = NULL;
        while (curr) {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }

    // ⚙️ Step 2: Main logic to add 1
    Node* addOne(Node* head) {
        // Reverse to simplify addition from LSB side
        head = reverse(head);

        Node* temp = head;
        int carry = 1;  // we are adding +1 to the number

        // Traverse and propagate carry
        while (temp && carry) {
            int sum = temp->data + carry;
            temp->data = sum % 10;
            carry = sum / 10;

            // Move to next if available
            if (temp->next)
                temp = temp->next;
            else
                break;
        }

        // If carry remains after the last node, create a new node
        if (carry)
            temp->next = new Node(carry);

        // Reverse back to restore original order
        head = reverse(head);
        return head;
    }
};

/*
────────────────────────────────────────────
🧩 Dry Run Example
────────────────────────────────────────────
Input:  1 → 9 → 9 → 9
Step 1: Reverse → 9 → 9 → 9 → 1
Step 2: Add 1
    9 + 1 = 10 → node = 0, carry = 1
    9 + 1 = 10 → node = 0, carry = 1
    9 + 1 = 10 → node = 0, carry = 1
    1 + 1 = 2  → node = 2, carry = 0
Step 3: Reverse again
Output: 2 → 0 → 0 → 0 ✅

────────────────────────────────────────────
🧭 Key Learnings:
────────────────────────────────────────────
✔ Reverse simplifies right-to-left arithmetic in linked lists.
✔ Carry propagates just like manual addition.
✔ Always handle leftover carry after final node.
✔ Reversing twice keeps the final order intact.
────────────────────────────────────────────
📈 Complexity:
Time:  O(n)
Space: O(1)
────────────────────────────────────────────
*/

