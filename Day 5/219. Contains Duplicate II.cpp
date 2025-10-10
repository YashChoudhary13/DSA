// 🔗 Problem Link:
// https://leetcode.com/problems/contains-duplicate-ii/
//
// 🧠 Problem Summary:
// Return true if there exist two indices i and j such that:
// nums[i] == nums[j]  and  |i - j| <= k
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: true
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window; // stores last k elements

        for (int i = 0; i < nums.size(); i++) {
            // Check if duplicate already exists in window
            if (window.count(nums[i])) return true;

            // Add current element to window
            window.insert(nums[i]);

            // Maintain window size ≤ k
            if (window.size() > k)
                window.erase(nums[i - k]);
        }

        return false;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
We need to detect duplicates within a distance of k.
So we maintain a sliding window of size k using a hash set.

Each iteration:
   - If nums[i] exists in window → duplicate found within k range → return true
   - Else insert nums[i]
   - If window exceeds size k → remove oldest element nums[i-k]
*/

// ---------------------------------------------------------------------------
// ⚙️ Example Dry Run:
// ---------------------------------------------------------------------------
/*
nums = [1,2,3,1], k = 3
i=0 → window = [1]
i=1 → window = [1,2]
i=2 → window = [1,2,3]
i=3 → nums[3] = 1 → already in window ✅ return true
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity:
// ---------------------------------------------------------------------------
/*
Time  → O(n)
Space → O(k)
*/

// ---------------------------------------------------------------------------
// 🧠 Learnings Recap:
// ---------------------------------------------------------------------------
/*
✅ Sliding window with size constraint (≤ k)
✅ Use hash set to detect duplicates efficiently
✅ Remove elements going out of the window
✅ Foundation for problems like:
   - Longest Substring Without Repeating Characters
   - Contains Duplicate III
   - Distinct Elements in Window
*/
// ---------------------------------------------------------------------------

// 🎯 Takeaway:
// Reuse the "contains duplicate" idea but limit the scope
// by maintaining a window of size k. This is a key real-world pattern.
// ---------------------------------------------------------------------------
