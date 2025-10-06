// Link to the problem:
// https://leetcode.com/problems/reverse-words-in-a-string-iii/description/

// Solution:
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int start = 0;
        int end = 0;
        for (int i = 0; i <= n; i++) {
            if (s[i] == ' ' || i == n) {
                end = i - 1;
                while (start < end) {
                    swap(s[start], s[end]);
                    start++;
                    end--;
                }
                start = i + 1;
            }
        }
        return s;
    }
};

// Learnings & Key Points:
/*
👉 Concept: Two Pointers (on String)
   - Use two pointers to reverse each word independently within a string.
   - Keep overall word order the same, only reverse characters within each word.

👉 Intuition I Had:
   - I knew I had to reverse each word one by one.
   - I used pointers `start` and `end` to mark the word boundaries.
   - I correctly handled the final word by checking `i == n`.
   - The main mistake was checking `if(i == ' ')` instead of `if(s[i] == ' ')`.

👉 My Mistake:
   - Compared index variable `i` directly with `' '` (ASCII 32),
     so the condition didn’t trigger at spaces.
   - Forgot to update `start` correctly for next word in initial draft.
   - Also used `<=` in `while` instead of `<`, which can cause double-swapping middle character.

👉 Correct Intuition Flow:
   1️⃣ Start scanning the string with pointer `i`.
   2️⃣ When you find a space or end of string (`i == n`):
       - Reverse the substring from `start` to `i-1`.
       - Move `start` to `i + 1` (next word start).
   3️⃣ Continue till end.
   4️⃣ Return modified string.

👉 Fixed Solution Steps:
   - `if (s[i] == ' ' || i == n)` → checks both space and last word.
   - `end = i - 1` → end of the current word.
   - Reverse using `while (start < end)`.
   - Move `start = i + 1` → next word start.

👉 Example walkthrough:
   Input:  "Let's take LeetCode contest"
   Output: "s'teL ekat edoCteeL tsetnoc"

   Stepwise:
   - First word: "Let's" → "s'teL"
   - Second: "take" → "ekat"
   - Third: "LeetCode" → "edoCteeL"
   - Fourth: "contest" → "tsetnoc"
   Combine → Final output.

👉 What I Learned:
   ✅ Two pointers work on strings just like arrays.
   ✅ Always check characters (`s[i]`) instead of indices (`i`).
   ✅ Remember to reset `start` after reversing a word.
   ✅ Keep `while(start < end)` to avoid extra middle swap.
   ✅ Small syntax errors don’t mean wrong logic — trust the thought process.

👉 Time & Space:
   - Time Complexity: O(n)
   - Space Complexity: O(1) (in-place reversal)
*/

// Key Takeaways:
/*
✅ Two-pointer logic applies equally to arrays and strings.
✅ Be careful with syntax: `s[i]` vs `i`.
✅ After reversing a segment, always move your start pointer correctly.
✅ Don’t overthink small bugs — your intuition was completely correct.
✅ This is a foundation for advanced string problems:
   - Reverse Words in a String II (#186)
   - Reverse Words in a String (#151)
   - Left/Right rotate string problems
*/