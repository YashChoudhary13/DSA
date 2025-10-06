// Link to the problem:
// https://leetcode.com/problems/minimum-size-subarray-sum/description/

// Solution:
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, sum = 0;
        int ans = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right]; // Expand the window by including nums[right]

            // Shrink window while it's valid
            while (sum >= target) {
                ans = min(ans, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return (ans == INT_MAX) ? 0 : ans;
    }
};

// Learnings & Key Points:
/*
👉 Concept: Sliding Window (Dynamic Window)
   - Expand window → by moving right pointer and adding to sum
   - Shrink window → while sum >= target, move left pointer and subtract from sum
   - Maintain the smallest window length that meets condition

👉 Why Sliding Window Works:
   - The array contains only positive integers.
   - Once sum >= target, moving left only reduces sum — this allows us to safely shrink.

👉 What I Initially Did:
   - Used if-else ladder instead of a while loop
   - Didn’t check all smaller valid windows before expanding again
   - Missed +1 in window size (since both left and right are inclusive)
   - Didn’t handle case when no subarray is found (ans == INT_MAX)

👉 Key Fixes / Things to Remember:
   - Always use `while (sum >= target)` → to keep shrinking until window becomes invalid
   - Window size = (right - left + 1)
   - Return 0 if no valid subarray found
   - Expand → check → shrink (that’s the rhythm of dynamic sliding window)
   - Works only for positive numbers — if negatives are involved, prefix sum or other methods are needed.

👉 Time & Space:
   - Time Complexity: O(n)
   - Space Complexity: O(1)
*/

// Example walkthrough:
/*
target = 7, nums = [2,3,1,2,4,3]

right = 0 → sum = 2 (<7)
right = 1 → sum = 5 (<7)
right = 2 → sum = 6 (<7)
right = 3 → sum = 8 (>=7)
   → window [0..3] = len 4 → ans = 4
   → shrink: sum -= 2 → sum = 6
right = 4 → sum = 10 (>=7)
   → window [1..4] = len 4 → ans = 4
   → shrink: sum -= 3 → sum = 7 (>=7)
   → window [2..4] = len 3 → ans = 3
   → shrink: sum -= 1 → sum = 6 (<7)
right = 5 → sum = 9 (>=7)
   → window [3..5] = len 3 → ans = 3
   → shrink: sum -= 2 → sum = 7 (>=7)
   → window [4..5] = len 2 → ans = 2
✅ Final answer = 2
*/

// Key Takeaways:
/*
✅ Understand when to expand vs. when to shrink.
✅ Sliding window = "keep valid window, shrink as much as possible".
✅ Don’t mix if-else, use while loop to continuously shrink.
✅ Handle no-result case with INT_MAX → 0 conversion.
✅ Foundational pattern for advanced problems:
   - Longest Substring Without Repeating Characters (#3)
   - Minimum Window Substring (#76)
   - Subarray Product Less Than K (#713)
*/
