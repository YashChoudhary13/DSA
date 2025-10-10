// 🔗 Problem Link:
// https://leetcode.com/problems/longest-continuous-increasing-subsequence/
//
// 🧠 Problem Summary:
// Given an unsorted array of integers nums, return the length of the
// longest *continuous* increasing subsequence.
//
// Continuous means elements must appear consecutively in the array.
//
// Example:
// Input: nums = [1,3,5,4,7]
// Output: 3
// Explanation: [1,3,5] is the longest continuous increasing subsequence.
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) return 0;

        int n = nums.size();
        int maxLength = 1;     // maximum streak found so far
        int currentLength = 1; // current increasing sequence length

        // Traverse from the 2nd element onward
        for (int j = 1; j < n; j++) {
            if (nums[j] > nums[j - 1]) {
                // increasing trend continues
                currentLength++;
            } else {
                // streak broke, reset current length
                currentLength = 1;
            }
            maxLength = max(maxLength, currentLength);
        }

        return maxLength;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
We want the *longest continuous* streak of increasing numbers.
That means as long as nums[j] > nums[j-1], we extend the sequence.
If the pattern breaks, we reset the current streak length to 1.

We track:
    - currentLength → how long the current increasing streak is.
    - maxLength     → the best streak seen so far.
*/

// ---------------------------------------------------------------------------
// ⚙️ Example Dry Run:
// ---------------------------------------------------------------------------
/*
nums = [1, 3, 5, 4, 7]

j = 1 → 3 > 1 → current = 2, max = 2
j = 2 → 5 > 3 → current = 3, max = 3
j = 3 → 4 <= 5 → reset current = 1
j = 4 → 7 > 4 → current = 2
✅ Final maxLength = 3
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis:
// ---------------------------------------------------------------------------
/*
Time  → O(n)
Space → O(1)
*/

// ---------------------------------------------------------------------------
// 🧩 Your Original Approach & Debugging Journey:
// ---------------------------------------------------------------------------
/*
✅ You correctly used two pointers (i, j) to simulate the window.
✅ You identified when to "reset" i (when sequence breaks).
✅ The bug came from:
     - comparing nums[j] <= nums[i] (non-adjacent)
     - stopping at j < nums.size() - 1 (missed last element)
✅ Once fixed → logic became identical to the clean O(n) approach above.

That’s the right “window reset” intuition — now you fully own this pattern.
*/

// ---------------------------------------------------------------------------
// 🧠 Learnings Recap:
// ---------------------------------------------------------------------------
/*
✅ For continuous sequences → always compare adjacent elements.
✅ When the pattern breaks, reset your counter.
✅ Keep global maximum tracked throughout.
✅ This is a foundation for harder problems like:
      - Longest Subarray of 1’s After Deletion
      - Longest Increasing Subsequence (non-continuous)
      - Longest Consecutive Sequence
✅ Pattern Name: "Sliding Window with Reset Condition"
*/

// ---------------------------------------------------------------------------
// 🎯 Takeaway:
// ---------------------------------------------------------------------------
/*
You don’t always need explicit 'left' and 'right' pointers.
For linear patterns like this, a simple counter and reset condition
make your code faster, cleaner, and easier to reason about.

This is how you should handle “continuous increasing” or “continuous valid” problems.
*/
// ---------------------------------------------------------------------------

