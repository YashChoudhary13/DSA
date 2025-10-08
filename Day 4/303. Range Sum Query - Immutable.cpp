// 🔗 Problem Link:
// https://leetcode.com/problems/range-sum-query-immutable/
//
// 🧠 Problem Summary:
// You are given an integer array nums.
// You need to efficiently answer multiple queries of the form:
//     sumRange(left, right)
// which returns the sum of all elements between left and right (inclusive).
//
// Example:
// Input:  nums = [-2, 0, 3, -5, 2, -1]
// Query:  sumRange(0, 2) → 1
// Query:  sumRange(2, 5) → -1
// Query:  sumRange(0, 5) → -3
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class NumArray {
public:
    vector<int> prefix;  // prefix[i] stores sum of first i elements (nums[0 ... i-1])

    // ✅ Constructor — Precompute prefix sums
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0); // +1 makes indexing easy
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    // ✅ Query — Return range sum in O(1)
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
If we store prefix[i] = sum(nums[0] ... nums[i-1]),
then sum from left to right can be found quickly using:

   sumRange(left, right) = prefix[right + 1] - prefix[left]

This works because:
   prefix[right + 1] = sum of elements up to index right
   prefix[left] = sum of elements before index left
Subtracting gives exactly the range sum.
*/

// ---------------------------------------------------------------------------
// 🧩 Example Dry Run:
// ---------------------------------------------------------------------------
/*
nums = [-2, 0, 3, -5, 2, -1]

prefix = [0, -2, -2, 1, -4, -2, -3]
(index)   0   1   2  3   4   5   6

Now:

sumRange(0, 2) = prefix[3] - prefix[0] = 1 - 0 = 1
sumRange(2, 5) = prefix[6] - prefix[2] = -3 - (-2) = -1
sumRange(0, 5) = prefix[6] - prefix[0] = -3 - 0 = -3
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis:
// ---------------------------------------------------------------------------
/*
Time  → O(n)   (to precompute prefix array once)
Query → O(1)   (constant time lookup)
Space → O(n+1) (prefix array)
*/

// ---------------------------------------------------------------------------
// 🧠 Learnings:
// ---------------------------------------------------------------------------
/*
✅ Use prefix arrays when you need repeated range sums efficiently.
✅ The trick: prefix of size (n+1) helps avoid boundary errors.
✅ This concept generalizes to 2D matrices and even dynamic structures (Segment Trees / Fenwick Trees).
✅ Think "Precompute once → Answer many queries fast".

Pattern Name: Prefix Sum for Range Queries
Used In:
   - Range Sum Query (Immutable / Mutable)
   - Subarray sum questions
   - Balance / Equilibrium problems
   - 2D matrix prefix queries
*/
// ---------------------------------------------------------------------------

// 🎯 Takeaway:
// Precomputation is your secret weapon when the same operation (like sum)
// has to be done many times efficiently.
// ---------------------------------------------------------------------------
