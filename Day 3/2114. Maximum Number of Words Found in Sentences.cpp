// 🔗 Problem Link:
// https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/
//
// 🧠 Problem Summary:
// You're given an array of strings `sentences`.
// Each string contains words separated by a single space (' ').
// You need to return the maximum number of words found in any single sentence.
//
// Example:
// Input: sentences = ["alice and bob love leetcode",
//                     "i think so too",
//                     "this is great thanks very much"]
// Output: 6
// Explanation: The first and last sentence both contain 6 words.
//
// ---------------------------------------------------------------------------

#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    int mostWordsFound(vector<string>& sentences) {
        int n = sentences.size();
        int ans = 0;  // ✅ Initialize with 0 since we are finding max value

        for (int i = 0; i < n; i++) {
            int m = sentences[i].size();
            int count = 1;  // ✅ Each sentence has at least 1 word

            // Loop through the sentence to count spaces
            for (int j = 0; j < m; j++) {
                if (sentences[i][j] == ' ')  // ✅ single quotes = char literal
                    count++;
            }

            ans = max(ans, count);
        }

        return ans;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
We know that every sentence has words separated by spaces.
So if a sentence has 'k' spaces, then it has (k + 1) words.

Example:
    "I love DSA" → 2 spaces → 3 words

Hence, to find the number of words in a sentence, we can simply count
how many spaces it has, add 1, and keep track of the maximum across all sentences.
*/

// ---------------------------------------------------------------------------
// 🧠 Your Original Thought Process:
// ---------------------------------------------------------------------------
/*
✅ You correctly looped through every sentence.
✅ You correctly looped through each character.
✅ You counted words based on spaces.

⚠️ Minor errors:
1. You initialized ans = INT_MAX → This made no sense for finding max.
   We need to start from 0 instead of the largest number.
2. You compared with " " (string literal) instead of ' ' (character literal).
   In C++, " " is a string; ' ' is a single character.

Those were minor syntax slips — your overall logic was 100% correct.
*/

// ---------------------------------------------------------------------------
// 🔍 Dry Run Example
// ---------------------------------------------------------------------------
/*
sentences = ["alice and bob love leetcode", "i think so too"]

→ sentence 1: "alice and bob love leetcode"
   spaces = 4 → words = 5

→ sentence 2: "i think so too"
   spaces = 3 → words = 4

ans = max(5, 4) = 5
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis
// ---------------------------------------------------------------------------
/*
Time Complexity: O(N * M)
    where N = number of sentences
          M = average length of each sentence
    → Because we check each character in each sentence once.

Space Complexity: O(1)
    → Only a few integer variables are used.
*/

// ---------------------------------------------------------------------------
// ✅ Learnings Recap
// ---------------------------------------------------------------------------
/*
✅ Use ' ' (single quotes) for character comparison.
✅ Initialize variables according to the operation (max → 0, min → INT_MAX).
✅ Counting logic: number of words = spaces + 1.
✅ Great example of simple yet clean string traversal.

⭐ Pattern:
   For counting elements separated by a single delimiter (space, comma, etc.),
   you can always count occurrences of the delimiter and add one.
*/

// ---------------------------------------------------------------------------
// 🎯 Takeaway:
// ---------------------------------------------------------------------------
/*
This is one of those "cool down" easy problems where the goal
is to solidify attention to small details and syntax correctness.
You already had the logic right — the fix was in initialization and char comparison.

Remember:
👉 Use ' ' for characters, not " ".
👉 Initialize based on whether you're finding max or min.
👉 A clean and readable solution beats an overcomplicated one any day.
*/
// ---------------------------------------------------------------------------
