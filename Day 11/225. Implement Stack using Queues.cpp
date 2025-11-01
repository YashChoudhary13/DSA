/*
📘 Day 11 — Stack & Queue Fundamentals
Problem: Implement Stack using Queues (Leetcode 225)

-------------------------------------------------------------
🎯 OVERVIEW
-------------------------------------------------------------
You’re asked to implement a **Stack (LIFO)** using **Queue (FIFO)** operations.

Operations required:
- push(x): Add an element on top of the stack
- pop(): Remove the top element
- top(): Get the top element
- empty(): Return whether the stack is empty

Key constraint: All must work using **queue operations only**.

-------------------------------------------------------------
🧠 INITIAL INTUITION
-------------------------------------------------------------
We know:
- Stack → Last In First Out
- Queue → First In First Out

So, when we `push(x)` into a stack, that element should come out first when popped.
But queue always removes the *earliest* inserted element.

💡 Idea:
If we can make the **newly inserted element come to the front** of the queue,
then the queue will behave exactly like a stack.

So after pushing `x`, we rotate the queue to bring `x` to the front.

-------------------------------------------------------------
🧩 INTUITION STEP-BY-STEP
-------------------------------------------------------------
Example:
push(1)
→ queue: [1]

push(2)
→ queue before rotation: [1, 2]
→ rotate once → [2, 1]

push(3)
→ queue before rotation: [2, 1, 3]
→ rotate twice → [3, 2, 1]

Now queue’s front = stack’s top.

pop() → removes front → behaves exactly like a stack pop.
top() → returns front → behaves like stack top.
empty() → same logic.

-------------------------------------------------------------
⚠️ COMMON CONFUSIONS
-------------------------------------------------------------
1️⃣ Declaring queue inside constructor
   ❌ Wrong: Each function gets a new empty queue.
   ✅ Fix: Declare queue as a **class member variable**.

2️⃣ Using .top() instead of .front()
   Queue has no `.top()` — use `.front()`.

3️⃣ Rotation count mistake
   Rotate (size - 1) times after pushing new element.

4️⃣ Leetcode test input confusion
   Input looks like:
     ["MyStack","push","push","top","pop","empty"]
     [[],[1],[2],[],[],[]]
   This just simulates method calls on your class.

-------------------------------------------------------------
✅ FINAL IMPLEMENTATION
-------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class MyStack {
public:
    queue<int> q;

    MyStack() {}

    void push(int x) {
        q.push(x);
        int size = q.size();
        for (int i = 0; i < size - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

/*
-------------------------------------------------------------
🧭 DRY RUN EXAMPLE
-------------------------------------------------------------
Input sequence:
push(1)
push(2)
top()
pop()
empty()

Simulation:
push(1) → [1]
push(2) → [1, 2] → rotate → [2, 1]
top()   → 2
pop()   → removes 2 → [1]
empty() → false

Output: [null, null, null, 2, 2, false]
-------------------------------------------------------------
*/

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    cout << s.top() << endl;   // 2
    cout << s.pop() << endl;   // 2
    cout << s.empty() << endl; // 0 (false)
}

/*
-------------------------------------------------------------
🧠 THINGS TO REMEMBER
-------------------------------------------------------------
1️⃣ Always declare data structure (queue) as a class member.
2️⃣ After pushing a new element, rotate queue (size - 1) times.
3️⃣ Queue’s front represents stack’s top.
4️⃣ Don’t worry about “weird” Leetcode inputs — they simulate method calls.
5️⃣ This is a single-queue implementation — most optimal.

-------------------------------------------------------------
⏱️ COMPLEXITY
-------------------------------------------------------------
| Operation | Time Complexity |
|------------|-----------------|
| push()     | O(n)            |
| pop()      | O(1)            |
| top()      | O(1)            |
| empty()    | O(1)            |

-------------------------------------------------------------
🧾 COMMIT MESSAGE
-------------------------------------------------------------
Day 11 — Implemented Stack using Queue (Single Queue Rotation) 🚀
-------------------------------------------------------------
*/
