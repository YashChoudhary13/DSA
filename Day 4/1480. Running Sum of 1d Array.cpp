// 🔗 Problem Link:
// https://leetcode.com/problems/running-sum-of-1d-array/
//
// 🧠 Problem Summary:
// Given an array nums, return an array where each element i
// contains the sum of all elements from index 0 to i.
//
// Example:
// Input:  nums = [1,2,3,4]
// Output: [1,3,6,10]
//
// Explanation:
// runningSum[0] = 1
// runningSum[1] = 1 + 2 = 3
// runningSum[2] = 1 + 2 + 3 = 6
// runningSum[3] = 1 + 2 + 3 + 4 = 10
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += nums[i];   // add current element to sum
            nums[i] = sum;    // replace nums[i] with prefix sum
        }

        return nums;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
Instead of calculating each prefix sum from scratch,
we can simply keep a running total as we move forward.

We start with sum = 0
At each step, we add nums[i] to sum and update nums[i].

That way, after processing index i:
    nums[i] = nums[0] + nums[1] + ... + nums[i]

This is the simplest form of "prefix sum".
*/

// ---------------------------------------------------------------------------
// 🧠 Your Approach (Perfect):
// ---------------------------------------------------------------------------
/*
✅ You used one running variable (sum) — O(1) space.
✅ You updated the array in-place — memory efficient.
✅ You made only one pass — O(n) time.
✅ You clearly understood the prefix idea.

This is the kind of neat, optimal code interviewers love to see.
*/

// ---------------------------------------------------------------------------
// 🧩 Example Dry Run:
// ---------------------------------------------------------------------------
/*
nums = [1, 2, 3, 4]
sum = 0

i=0 → sum = 1 → nums = [1, 2, 3, 4]
i=1 → sum = 3 → nums = [1, 3, 3, 4]
i=2 → sum = 6 → nums = [1, 3, 6, 4]
i=3 → sum =10 → nums = [1, 3, 6, 10]

✅ Output: [1, 3, 6, 10]
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis:
// ---------------------------------------------------------------------------
/*
Time  → O(n)   (single pass)
Space → O(1)   (in-place)
*/

// ---------------------------------------------------------------------------
// 🎯 Learnings & Pattern Recognition:
// ---------------------------------------------------------------------------
/*
✅ This is your first PREFIX SUM pattern:
     prefix[i] = prefix[i-1] + nums[i]
✅ You can reuse this logic for:
     - Range sum queries
     - Balance index problems
     - Cumulative frequency problems

🧩 Key Formula:
   prefixSum[i] = prefixSum[i-1] + nums[i]

🧠 Tip:
   If an array question involves "sum from 0 to i" repeatedly,
   always think of prefix sums.
*/
// ---------------------------------------------------------------------------

