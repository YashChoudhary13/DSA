/*
────────────────────────────────────────────
🧠 Day 7 – Q3 | Convert Binary Number in a Linked List to Integer
LeetCode: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
Difficulty: Easy
────────────────────────────────────────────

💭 Problem:
We are given a linked list representing a binary number (most significant bit first),
and we need to return its decimal (integer) value.

Example:
Input:  1 → 0 → 1
Output: 5   (because 101₂ = 5₁₀)

────────────────────────────────────────────
💡 Intuition: “Base Accumulation” Pattern
────────────────────────────────────────────
We often think of binary-to-decimal as:
   (1 * 2²) + (0 * 2¹) + (1 * 2⁰)

But in a linked list, we don’t know the total length or position
until we’ve traversed it completely.

So instead of using exponents, we can *build the number progressively*
as we move through the list — exactly like how we build a decimal number.

For example:
Decimal digits: 1 → 2 → 3
value = ((1)*10 + 2)*10 + 3 = 123

In binary (base 2):
Binary digits: 1 → 0 → 1
value = ((1)*2 + 0)*2 + 1 = 5

Thus, the core formula:
──────────────────────
    value = value * base + current_digit
──────────────────────
For binary → base = 2
Hence:
    value = value * 2 + node->val;

Every new node “shifts” the old digits left by one bit (×2)
and adds the new bit at the end.

────────────────────────────────────────────
🧩 Example Dry Run
────────────────────────────────────────────
Input:  1 → 0 → 1

Step 1: value = 0
Step 2: value = 0*2 + 1 = 1
Step 3: value = 1*2 + 0 = 2
Step 4: value = 2*2 + 1 = 5

Output = 5 ✅

────────────────────────────────────────────
🔑 Things to Remember:
────────────────────────────────────────────
• This formula (value = value * base + digit) applies to ALL number systems.
• In binary, base = 2; in decimal, base = 10.
• It works left-to-right, no need for powers or knowing length.
• Can be written as: value = (value << 1) | node->val; (bit version)

────────────────────────────────────────────
⚙️ Complexity:
Time:  O(n)  → single traversal
Space: O(1)  → constant extra memory
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
    int getDecimalValue(ListNode* head) {
        int value = 0;
        ListNode* temp = head;

        while (temp != nullptr) {
            value = value * 2 + temp->val;  // progressively build the number
            temp = temp->next;
        }

        return value;
    }
};
