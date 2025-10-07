// 🔗 Problem Link:
// https://leetcode.com/problems/merge-strings-alternately/
//
// 🧠 Problem Summary:
// Merge two strings by taking characters alternately from each.
// If one string is longer, append the rest at the end.
//
// Example:
// word1 = "abc", word2 = "pqrstu"
// Output = "apbqcrstu"
//
// ---------------------------------------------------------------------------

#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        int i = 0, j = 0;
        string merged = "";

        // Add one character from each alternately
        while (i < n && j < m) {
            merged += word1[i++];
            merged += word2[j++];
        }

        // Add leftover characters (if any)
        while (i < n) merged += word1[i++];
        while (j < m) merged += word2[j++];

        return merged;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// We interleave letters from word1 and word2.
// If one string runs out first, we just add the rest of the other.
//
// Think of two hands holding two decks of letters,
// dropping them alternately to make a combined deck.
// ---------------------------------------------------------------------------
//
// 🧠 Learnings:
// ✅ When looping through two arrays/strings, always use `&&` to avoid out-of-bound errors.
// ✅ Append remaining elements separately to handle unequal lengths.
// ✅ Great practice for two-pointer pattern.
//
// ---------------------------------------------------------------------------
//
// 🧩 Complexity:
// Time  → O(n + m)
// Space → O(n + m)
//
// ---------------------------------------------------------------------------
//
// 🎯 Example Dry Run:
// word1 = "abc", word2 = "pqrstu"
// merged = "apbqcrstu"
// ---------------------------------------------------------------------------
