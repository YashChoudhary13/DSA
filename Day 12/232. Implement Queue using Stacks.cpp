/*
📘 Day 11 — Stack & Queue Fundamentals
Problem: Implement Queue using Stacks (Leetcode 232)

-------------------------------------------------------------
🎯 OVERVIEW
-------------------------------------------------------------
We need to design a **Queue (FIFO)** using **Stacks (LIFO)**.

Supported operations:
- push(x): Insert element at the back
- pop(): Remove element from the front
- peek(): Get the front element
- empty(): Check if the queue is empty

-------------------------------------------------------------
🧠 INTUITION
-------------------------------------------------------------
Stack removes the *last inserted* element first (LIFO).
Queue removes the *first inserted* element first (FIFO).

To fix this reversal, we use **two stacks**:
- One temporary stack to reverse order when pushing.
- One main stack to always keep the *front* element on top.

The trick:
> Before inserting a new element, move everything from s1 → s2.
> Then push the new element into s1.
> Then move everything back from s2 → s1.

Now s1.top() will always represent the *front of the queue*.

-------------------------------------------------------------
✅ FINAL IMPLEMENTATION
-------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class MyQueue {
public:
    stack<int> s1, s2;

    MyQueue() {}

    void push(int x) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(x);
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    int pop() {
        int x = s1.top();
        s1.pop();
        return x;
    }

    int peek() {
        return s1.top();
    }

    bool empty() {
        return s1.empty();
    }
};

/*
-------------------------------------------------------------
🧭 DRY RUN EXAMPLE
-------------------------------------------------------------
push(1)
→ s1: [1]
push(2)
→ move 1 to s2, push 2, move 1 back
→ s1: [1 (bottom), 2 (top)]
peek() → 1
pop()  → remove 1
→ s1: [2]
empty() → false
-----------------------------------
*/