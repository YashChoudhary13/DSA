// 🔗 Problem: https://practice.geeksforgeeks.org/problems/flattening-a-linked-list/3500/
// 🎯 Topic: Linked List - Recursion + Merge Pattern

/*
🧠 Intuition:
We are given a linked list where each node has:
- a 'next' pointer → points to the next list
- a 'bottom' pointer → points to a sorted vertical sub-list

Goal:
Flatten all lists into a single sorted list using 'bottom' pointers only.

🔍 Observation:
- Each vertical list is already sorted.
- The overall problem can be broken down into smaller identical subproblems.

So we can use recursion:
1️⃣ Flatten the list to the right (root->next)
2️⃣ Merge current list with that flattened result
3️⃣ Return the merged list (connected only through 'bottom')

This is similar to the merge step of Merge Sort.
*/
class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = nullptr;
        bottom = nullptr;
    }
};

class Solution {
  public:
    // 🔧 Helper function to merge two sorted lists
    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        Node* result;

        if (a->data < b->data) {
            result = a;
            result->bottom = merge(a->bottom, b);
        } else {
            result = b;
            result->bottom = merge(a, b->bottom);
        }

        result->next = nullptr; // ignore next pointers in final result
        return result;
    }

    // 🚀 Main flatten function
    Node* flatten(Node* root) {
        if (!root || !root->next) return root;

        // Flatten the list to the right
        root->next = flatten(root->next);

        // Merge current list with the flattened one
        root = merge(root, root->next);

        return root;
    }
};

/*
🧪 Dry Run:
Input:
5 -> 10 -> 19 -> 28
|    |     |     |
7    20    22    35
|          |     |
8          50    40
|                |
30               45

flatten(28) → 28
flatten(19) → merge([19,22,50], [28,35,40,45])
flatten(10) → merge([10,20], flattened(19))
flatten(5) → merge([5,7,8,30], flattened(10))

✅ Output (bottom pointers):
5 → 7 → 8 → 10 → 19 → 20 → 22 → 28 → 30 → 35 → 40 → 45 → 50

⏱️ Complexity:
Time: O(N * M) — merging each sublist once
Space: O(1) — only recursion stack

📘 Learnings:
- Always identify smaller subproblems → flatten(root->next)
- Merging is a common DSA backbone (used in recursion, divide-conquer)
- Trust recursion to “handle the rest” — just focus on merging current result
*/
