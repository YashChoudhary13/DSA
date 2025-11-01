/*
📘 Day 11 — Stack Applications
Problem: Longest Valid Parentheses (Leetcode 32)

-------------------------------------------------------------
🎯 OVERVIEW
-------------------------------------------------------------
Given a string containing only '(' and ')',
find the **length of the longest valid (well-formed) parentheses substring**.

-------------------------------------------------------------
🧠 INTUITION
-------------------------------------------------------------
We use a **stack of indices** to track the boundaries
of valid parentheses sequences.

Key idea:
- Push `-1` initially to mark the "base" before any valid substring.
- When we see '(' → push its index.
- When we see ')' → pop the top.
    - If stack becomes empty → push current index (new base).
    - Else → length = current_index - top_of_stack.
      That gives the current valid substring length.

This ensures we always measure the **distance between matched pairs**
and correctly reset when invalid ')' breaks continuity.

-------------------------------------------------------------
✅ FINAL IMPLEMENTATION
-------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i); // reset base
                } else {
                    ans = max(ans, i - st.top());
                }
            }
        }
        return ans;
    }
};

/*
-------------------------------------------------------------
🧭 DRY RUN EXAMPLE
-------------------------------------------------------------
s = "()(()"
indexes:  0 1 2 3 4
stack process:
i=0 '(' → push 0 → [-1,0]
i=1 ')' → pop 0 → [-1] → ans = 1 - (-1) = 2
i=2 '(' → push 2 → [-1,2]
i=3 '(' → push 3 → [-1,2,3]
i=4 ')' → pop 3 → [-1,2] → ans = max(2, 4-2=2)

Final ans = 2
✅ Longest valid substring length = 2
-------------------------------------------------------------
*/

int main() {
    Solution sol;
    cout << sol.longestValidParentheses("()(()") << endl; // Output: 2
}

/*
-------------------------------------------------------------
🧠 INTUITION RECAP
-------------------------------------------------------------
| Stack stores | Indexes of '(' and unmatched ')' |
| Base (-1) | Helps compute valid substring length |
| Why it works | Measures continuous valid ranges |
| Key operation | ans = max(ans, i - st.top()) |

-------------------------------------------------------------
⏱️ COMPLEXITY
-------------------------------------------------------------
| Operation | Time | Space |
|------------|-------|--------|
| Traversal  | O(n)  | O(n)  |

-------------------------------------------------------------
🧾 COMMIT MESSAGE
-------------------------------------------------------------
Day 11 — Longest Valid Parentheses (Index Stack + Base Tracking) 🚀
-------------------------------------------------------------
*/
