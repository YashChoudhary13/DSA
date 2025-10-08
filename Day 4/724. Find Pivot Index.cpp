// 🔗 Problem Link:
// https://leetcode.com/problems/find-pivot-index/
//
// 🧠 Problem Summary:
// Given an array nums, return the pivot index where the sum of all numbers
// strictly to the left equals the sum of all numbers strictly to the right.
//
// Example:
// Input:  nums = [1,7,3,6,5,6]
// Output: 3
// Explanation:
// The sum to the left of index 3 (1+7+3 = 11)
// The sum to the right of index 3 (5+6 = 11)
// Hence, 3 is the pivot index.
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();

        // ✅ Step 1: Create prefix & suffix arrays
        vector<int> prefix(n, 0);
        vector<int> suffix(n, 0);

        // ✅ Step 2: Fill prefix array
        int sum = 0;
        for (int i = 0; i < n; i++) {
            prefix[i] = sum;
            sum += nums[i];
        }

        // ✅ Step 3: Fill suffix array
        sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = sum;
            sum += nums[i];
        }

        // ✅ Step 4: Find index where prefix == suffix
        for (int i = 0; i < n; i++) {
            if (prefix[i] == suffix[i])
                return i;
        }

        return -1; // if no pivot index found
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
A pivot index divides the array into two parts such that:

   left sum  ==  right sum

To make this efficient, we precompute:
   prefix[i] = sum of all elements before i
   suffix[i] = sum of all elements after i

Then we just need to find i where prefix[i] == suffix[i].
*/

// ---------------------------------------------------------------------------
// 🧩 Example Dry Run:
// ---------------------------------------------------------------------------
/*
nums = [1, 7, 3, 6, 5, 6]
n = 6

prefix[] = [0, 1, 8, 11, 17, 22]
suffix[] = [27, 20, 17, 11, 6, 0]

i=0 → 0 != 27
i=1 → 1 != 20
i=2 → 8 != 17
i=3 → 11 == 11 ✅ pivot index = 3

Return 3
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis:
// ---------------------------------------------------------------------------
/*
Time  → O(n)  (two passes for prefix + suffix)
Space → O(n)  (prefix and suffix arrays)
*/

// ---------------------------------------------------------------------------
// ⚡ Optimized Version (O(1) Space):
// ---------------------------------------------------------------------------
/*
Instead of storing prefix/suffix arrays,
we can maintain a running left sum and compute right sum using total sum.

Formula:
    rightSum = totalSum - leftSum - nums[i]
*/

class OptimizedSolution {
public:
    int pivotIndex(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int leftSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            int rightSum = total - leftSum - nums[i];
            if (leftSum == rightSum) return i;
            leftSum += nums[i];
        }
        return -1;
    }
};

// ---------------------------------------------------------------------------
// 🧠 Learnings Recap:
// ---------------------------------------------------------------------------
/*
✅ When you see “sum of elements before and after index i”, think PREFIX SUMS.
✅ Never write into an uninitialized vector — always set size first: vector<int>(n, 0).
✅ You can often optimize prefix/suffix logic using totalSum and one running variable.
✅ Core reusable pattern for range sum and balance problems.

⭐ Pattern Name: Prefix-Sum Balance
   Used In:
     - Find Pivot Index (#724)
     - Equilibrium Point
     - Range Sum Queries
     - Minimum Average Difference
*/
// ---------------------------------------------------------------------------
