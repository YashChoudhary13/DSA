// Link to the problem:
// https://leetcode.com/problems/product-of-array-except-self/description/

// Solution:
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        // Prefix array stores product of all elements before the current index
        vector<int> prefix(n);
        prefix[0] = 1;
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }

        // Suffix array stores product of all elements after the current index
        vector<int> suffix(n);
        suffix[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }

        // Final result: multiply prefix[i] * suffix[i]
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = prefix[i] * suffix[i];
        }

        return ans;
    }
};

// Learning:
/*
👉 Concept: Prefix–Suffix Multiplication (No Division)
We can’t use division here, so we precompute:
- prefix[i] = product of all elements before index i
- suffix[i] = product of all elements after index i
Then for each i, result[i] = prefix[i] * suffix[i].

Example:
nums = [1, 2, 3, 4]

prefix = [1, 1, 2, 6]
suffix = [24, 12, 4, 1]

result = [1*24, 1*12, 2*4, 6*1] = [24, 12, 8, 6]
*/

// Why this works:
/*
At every index i:
- prefix[i] gives product of everything to its left
- suffix[i] gives product of everything to its right
Multiplying them gives total product except nums[i].
*/

// Time & Space:
/*
Time Complexity: O(n)
Space Complexity: O(n)  // can be optimized to O(1) using prefix + running suffix
*/

// Extra Understanding:
/*
👉 prefix–suffix patterns are super powerful:
   - This one uses multiplication
   - Others use addition (prefix sum)
   - Or even bitwise operations in some problems

👉 If interviewer asks for O(1) space, we can reuse the result array itself:
   1st pass builds prefix
   2nd pass multiplies suffix directly
   (We’ll check that version tomorrow.)
*/

// Key Takeaways:
/*
✅ Classic O(n) array problem, no division.
✅ Demonstrates prefix-suffix thinking — a recurring DSA pattern.
✅ Foundation for:
   - Left-right accumulation problems
   - Trapping Rain Water (similar prefix–suffix logic)
   - Range product/sum type questions
*/
