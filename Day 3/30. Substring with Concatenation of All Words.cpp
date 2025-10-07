// 🔗 Problem: https://leetcode.com/problems/substring-with-concatenation-of-all-words/
// 🧠 Concept: Sliding Window + Fixed Word Size Alignment + HashMaps

/*
-------------------------------------------------------
👑 Problem Summary:
-------------------------------------------------------
You’re given:
    - A string s
    - A list of words[] (each of same length)

You must find **all starting indices** in s where
a substring is formed by concatenating *all words* exactly once
(in any order, without extra characters).

Example:
    s = "barfoothefoobarman"
    words = ["foo","bar"]

Output:
    [0,9]
Because:
    "barfoo" starts at index 0 ✅
    "foobar" starts at index 9 ✅

Each valid substring has:
    length = wordSize * wordCount
-------------------------------------------------------
*/


// -----------------------------------------------------
// ⚡ First, let's start from your ORIGINAL INTUITION
// -----------------------------------------------------
/*
Your early logic was beautiful:

    for (int i = 0; i < n - windowSize; i++) {
        string window = s.substr(i, windowSize);
        check all sub-words of size wordSize inside 'window';
    }

You realized:
✅ total window size = wordCount * wordSize
✅ we must check words in chunks (not chars)
✅ we can use a set/map to check if words exist
✅ we must ensure all words are found exactly once

That intuition was PERFECT.

But this approach had one issue:
- It rechecked *every window from scratch*, making it O(n * wordCount).
- That’s why it failed large repetitive cases (like "aaaaaaaa...").

So we’ll build on your foundation and make it smarter:
Instead of rechecking everything, we’ll make the window *slide dynamically*.
*/


// -----------------------------------------------------
// ⚙️ STEP 1: Build Word Frequency Map
// -----------------------------------------------------
/*
We first count how many times each word appears in 'words'.

Example:
    words = ["foo", "bar"]
    wordFreq = {
        "foo" : 1,
        "bar" : 1
    }

If words = ["foo","foo","bar"], then:
    wordFreq = {
        "foo" : 2,
        "bar" : 1
    }

We'll use this to compare against the words we find in s.
*/


// -----------------------------------------------------
// ⚙️ STEP 2: Understand WORD SIZE ALIGNMENT (OFFSET)
// -----------------------------------------------------
/*
Suppose wordSize = 3 (like "foo" or "bar").

We can cut s in 3 different ways:

Offset = 0 → [bar][foo][the][foo][bar][man]
Offset = 1 → b[arf][oot][hef][oob][arm]a[n]
Offset = 2 → ba[rfo][oth][efo][oba][rma][n]

We must try all offsets 0, 1, 2
because valid substrings might start at index 0, 1, or 2.

So, our outermost loop runs from offset = 0 to wordSize-1.
*/


// -----------------------------------------------------
// ⚙️ STEP 3: Define LEFT and RIGHT pointers
// -----------------------------------------------------
/*
Now, for each offset alignment:

    left  = start of the current window
    right = where we’re reading the next word from

We will move 'right' forward by wordSize each time (not by 1).

We use:
    string word = s.substr(right, wordSize);

If the word is valid (exists in wordFreq), we add it to our 'seen' map.

If we see an invalid word, or we see a word too many times,
we move 'left' forward (removing old words) until window becomes valid again.

When the number of valid words in our window == total wordCount,
we’ve found a perfect substring — record 'left' as a valid start.
*/


// -----------------------------------------------------
// ⚙️ STEP 4: Sliding Window Rules
// -----------------------------------------------------
/*
We maintain:
    unordered_map<string, int> seen; // current counts of words in the window
    int count = 0; // total words currently matched in window

Algorithm inside each offset pass:

1️⃣ Extract the next word at index 'right':
        word = s.substr(right, wordSize)

2️⃣ If word is valid (found in wordFreq):
        seen[word]++, count++

3️⃣ If word appears too many times (seen[word] > wordFreq[word]):
        shrink window from the left side until valid again:
            while (seen[word] > wordFreq[word]):
                leftWord = s.substr(left, wordSize)
                seen[leftWord]--
                count--
                left += wordSize;

4️⃣ If all words matched (count == wordCount):
        record left → ans.push_back(left)
        then slide left by one word to continue searching (to allow overlaps)

5️⃣ If word is invalid (not found in wordFreq):
        clear window → seen.clear(), count=0, left = right + wordSize

That’s the full logic cycle.
*/


// -----------------------------------------------------
// 💡 STEP 5: Time Complexity Intuition
// -----------------------------------------------------
/*
In the old approach:
    - For every i (n times), you checked every word inside (wordCount times)
    - That made it O(n * wordCount)
    - Also every substring() call made it worse

In this new approach:
    - We move right and left in steps of wordSize
    - Each word enters and leaves the window at most once per offset
    - So total time per offset ≈ O(n / wordSize)
    - And there are wordSize offsets
    → total ≈ O(n)

That’s why this solution passes all test cases.
*/


// -----------------------------------------------------
// ✅ FINAL IMPLEMENTATION
// -----------------------------------------------------
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        int wordSize = words[0].size();
        int wordCount = words.size();
        int windowSize = wordSize * wordCount;
        vector<int> ans;

        // Base case
        if (n < windowSize) return ans;

        // 1️⃣ Count expected frequency of each word
        unordered_map<string, int> wordFreq;
        for (auto &w : words)
            wordFreq[w]++;

        // 2️⃣ Try each possible starting offset (0, 1, 2, ... wordSize-1)
        for (int offset = 0; offset < wordSize; offset++) {

            int left = offset;          // left pointer for current window
            int count = 0;              // number of valid words matched so far
            unordered_map<string, int> seen; // words currently in window

            // 3️⃣ Move right pointer word-by-word
            for (int right = offset; right + wordSize <= n; right += wordSize) {

                string word = s.substr(right, wordSize);

                // Case A: The word exists in our dictionary
                if (wordFreq.count(word)) {
                    seen[word]++;
                    count++;

                    // If we saw this word too many times → shrink from left
                    while (seen[word] > wordFreq[word]) {
                        string leftWord = s.substr(left, wordSize);
                        seen[leftWord]--;
                        count--;
                        left += wordSize; // move left forward by one word
                    }

                    // If all words matched perfectly
                    if (count == wordCount) {
                        ans.push_back(left);

                        // Slide window forward to look for next match
                        string leftWord = s.substr(left, wordSize);
                        seen[leftWord]--;
                        count--;
                        left += wordSize;
                    }
                }

                // Case B: The word is invalid (not in wordFreq)
                else {
                    // Reset the window completely
                    seen.clear();
                    count = 0;
                    left = right + wordSize;
                }
            }
        }

        return ans;
    }
};


// -----------------------------------------------------
// 🧩 STEP 6: Example Walkthrough (barfoothefoobarman)
// -----------------------------------------------------
/*
offset = 0 → checking words at indices [0,3,6,9,12,15]
    [bar][foo][the][foo][bar][man]
    right=0  → word="bar" → seen["bar"]=1
    right=3  → word="foo" → seen["foo"]=1 → count=2 == wordCount
    ✅ found valid substring at left=0
    Slide left: remove "bar", count=1, left=3
    right=6  → word="the" → invalid → reset window
    right=9  → word="foo" → seen["foo"]=1
    right=12 → word="bar" → seen["bar"]=1 → count=2 == wordCount
    ✅ found valid substring at left=9
    Slide left: remove "foo", count=1, left=12
    right=15 → word="man" → invalid → reset

Result = [0,9]
*/


// -----------------------------------------------------
// 🧠 STEP 7: Key Learnings Recap
// -----------------------------------------------------
/*
✅ Offset = ensures we check all possible word-boundary alignments
✅ Left pointer = where current valid window starts
✅ Right pointer = where we add next word
✅ Shrinking logic keeps window valid
✅ Using 'seen' map avoids recomputing from scratch
✅ O(n) efficiency comes from reusing state across windows
✅ Concept generalizes to other advanced problems:
   - Minimum Window Substring (#76)
   - Find All Anagrams in a String (#438)
   - Permutation in String (#567)

This pattern = “Sliding window with word-aligned chunks”.
Remember: when all sub-strings are of equal fixed size, this logic pattern is GOLD.
*/


// -----------------------------------------------------
// 🎯 Final Thought
// -----------------------------------------------------
/*
This problem feels hard at first because your brain tries to think in characters,
but here, you must think in WORD BLOCKS.

Once you understand that:
    - offset controls word alignment,
    - left/right control the active word window,
    - and the maps ensure correct frequency tracking,
the logic becomes crystal clear.

Takeaway:
"Don't check every possible start one-by-one; 
 move the window intelligently in WORD STEPS."
*/
