// Link to the problem:
// https://leetcode.com/problems/subarray-sum-equals-k/description/

// Solution:
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1; // Initialize: prefix sum 0 occurs once (for subarrays starting at index 0)
        int currSum = 0;
        int ans = 0;

        for (int x : nums) {
            currSum += x; // running prefix sum

            // Check if there exists a prefix sum such that currSum - prefixSum = k
            if (mp.count(currSum - k)) {
                ans += mp[currSum - k];
            }

            // Store/update current prefix sum frequency
            mp[currSum]++;
        }

        return ans;
    }
};

// Learning:
/*
👉 Concept: Prefix Sum + HashMap

We use the idea that:
For any subarray (j+1 ... i),
sum(j+1...i) = prefix[i] - prefix[j]

For this subarray to have sum == k,
we need prefix[i] - prefix[j] = k  →  prefix[j] = prefix[i] - k

So if we know how many times (prefix[i] - k) appeared before,
we can count those many subarrays ending at index i.

We maintain:
unordered_map<int, int> mp → { prefix_sum : frequency }

At every index:
- Add current number to currSum
- If (currSum - k) exists in map, add its frequency to answer
- Update mp[currSum]++

We also initialize mp[0] = 1 to count subarrays starting at index 0.

Time Complexity: O(n)
Space Complexity: O(n)
*/

// Why we don’t check (currSum > k):
/*
Because elements can be negative. 
Even if currSum > k at some point, later elements (if negative) can reduce the sum back to k.
Thus, we must check for all cases without skipping.
*/

// Additional Understanding:
/*
Example: nums = [1, 2, 3], k = 3

prefix sums: [1, 3, 6]

We track:
mp[0] = 1 initially (for subarrays from start)

Step by step:
currSum = 1 → currSum - k = -2 (not found)
mp = {0:1, 1:1}

currSum = 3 → currSum - k = 0 (found once)
ans = 1 (subarray [1,2])
mp = {0:1, 1:1, 3:1}

currSum = 6 → currSum - k = 3 (found once)
ans = 2 (subarray [3])
mp = {0:1, 1:1, 3:1, 6:1}
*/

// Key Takeaways:
/*
✅ Prefix Sum helps reuse computed sums instead of recalculating.
✅ HashMap stores how many prefix sums have been seen before.
✅ Works with negative numbers, zeros, and positives.
✅ A core pattern used in many problems:
   - Subarray Sum Divisible by K (#974)
   - Binary Subarrays with Sum (#930)
   - Continuous Subarray Sum (#523)
*/
