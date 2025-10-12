/*
────────────────────────────────────────────
🧠 Day 6 - Q1 | Minimum Window Substring
LeetCode: https://leetcode.com/problems/minimum-window-substring/
Difficulty: Medium
Topic: Sliding Window + Hashmap
────────────────────────────────────────────

🧩 Problem:
Given two strings s and t, return the minimum window substring of s 
such that every character in t (including duplicates) is included 
in the window. If no such substring exists, return "".

────────────────────────────────────────────
💭 Intuition:
────────────────────────────────────────────
I initially thought:
  - Keep counts for t (tm)
  - Expand window and count matching characters (sm)
  - When counts match, record substring

But the *real key* insight:
  ✅ It's not about total matched characters,
     it's about how many **distinct characters**
     have met their required frequency.

So:
  - Maintain `tm` = required char counts.
  - Maintain `sm` = counts in current window.
  - Track `formed` → how many distinct chars currently satisfied.
  - When `formed == required`, window is valid.
  - Then try shrinking from the left to minimize it.

This “expand–check–shrink” cycle is the heart of all advanced sliding window problems.

────────────────────────────────────────────
🧱 Problems Faced:
────────────────────────────────────────────
❌ 1. Used `count == t.size()` instead of distinct satisfied chars.
❌ 2. Incremented count when `sm[x] < tm[x]` (wrong logic).
❌ 3. Shrink condition used wrong variable (`x` instead of `s[l]`).
❌ 4. Missed reducing count when removing from left.
❌ 5. Used `substr(j, i+1)` — forgot second param is length.
❌ 6. Updated answer before shrinking the window fully.

These mistakes made my window expand correctly but shrink incorrectly.

────────────────────────────────────────────
🔑 Things to Remember:
────────────────────────────────────────────
1. **Track distinct satisfied chars** → `formed == required`.
2. **Expand → check → shrink** is the flow.
3. **Always shrink while valid**, not when invalid.
4. **Decrement formed** when removing a char that breaks a requirement.
5. Use `s.substr(start, len)` → len = `r - l + 1`.
6. The order: add right → check valid → shrink left → record answer.

────────────────────────────────────────────
📘 Takeaways:
────────────────────────────────────────────
- Think in terms of “conditions satisfied,” not “characters matched.”
- Maintain two pointers carefully; every move changes state.
- Sliding window problems are mostly about defining what makes a window valid.
- This exact pattern repeats in:
   → Permutation in String
   → Find All Anagrams
   → Longest Substring with K Distinct Characters
   → Minimum Window Subsequence (hard)

────────────────────────────────────────────
⏱️ Complexity:
────────────────────────────────────────────
Time: O(|s| + |t|) → each char enters/exits window once.
Space: O(k) → k distinct characters in t (bounded by alphabet size).

────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.size() > s.size()) return "";

        unordered_map<char, int> tm, sm;
        for (char c : t) tm[c]++;

        int required = tm.size();  // distinct chars to satisfy
        int formed = 0;            // distinct chars currently satisfied
        int l = 0, r = 0;
        int minLen = INT_MAX, start = 0;

        while (r < s.size()) {
            char c = s[r];
            sm[c]++;

            if (tm.count(c) && sm[c] == tm[c])
                formed++;

            // shrink from left while valid
            while (l <= r && formed == required) {
                if (r - l + 1 < minLen) {
                    minLen = r - l + 1;
                    start = l;
                }

                char d = s[l];
                sm[d]--;
                if (tm.count(d) && sm[d] < tm[d])
                    formed--;
                l++;
            }

            r++;
        }

        return (minLen == INT_MAX) ? "" : s.substr(start, minLen);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    cout << sol.minWindow("ADOBECODEBANC", "ABC") << "\n"; // Expected: "BANC"
    return 0;
}
