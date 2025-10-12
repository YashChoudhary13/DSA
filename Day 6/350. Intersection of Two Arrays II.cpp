/*
────────────────────────────────────────────
🧠 Day 6 – Q2 | Intersection of Two Arrays II
LeetCode: https://leetcode.com/problems/intersection-of-two-arrays-ii/
Difficulty: Easy
Topic: Hashmap / Two Pointers
────────────────────────────────────────────

💭 My First Attempt:
────────────────────────────────────────────
I tried using two pointers directly on nums1 and nums2:

    int i = 0, j = 0;
    vector<int> ans;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) ans.push_back(nums1[i]);
        else if (nums1.size() > nums2.size()) i++;
        else j++;
    }

🧩 Problems in This Logic:
────────────────────────────────────────────
1. I compared based on array SIZE instead of VALUE → wrong pointer movement.
2. I forgot to SORT arrays first — two-pointer intersection only works on sorted data.
3. Without sorting, the comparison order is meaningless, so matches are missed.

────────────────────────────────────────────
✅ Corrected Two-Pointer Approach:
────────────────────────────────────────────
1. Sort both arrays.
2. Move pointers based on value comparison:
     - nums1[i] < nums2[j] → i++
     - nums1[i] > nums2[j] → j++
     - equal → add to answer and move both.

────────────────────────────────────────────
⚡ Hashmap Approach (More General):
────────────────────────────────────────────
Use a frequency map for nums1, then traverse nums2:
  - If element exists with count > 0 → add to result and decrement count.

✔ Works even when arrays are unsorted.
✔ O(n + m) time, O(min(n, m)) space.

────────────────────────────────────────────
🔑 Things to Remember:
────────────────────────────────────────────
• Two-Pointer → Only when both arrays are sorted.
• Hashmap → When arrays are unsorted or large.
• Move pointers based on VALUES, not indices or sizes.
• Hashmap gives linear time but uses extra memory.
• Sorting + two-pointers gives O(1) space but O(n log n) time.

────────────────────────────────────────────
📘 Takeaways:
────────────────────────────────────────────
- Learned that choosing between hashing and sorting depends on data properties.
- Always reason about the *ordering assumption* before using two-pointers.
- In interviews: explain both and justify which one fits the scenario better.
────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Method 1: Hashmap (for unsorted arrays)
    vector<int> intersect_map(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> freq;
        for (int x : nums1) freq[x]++;
        vector<int> ans;
        for (int y : nums2) {
            if (freq[y] > 0) {
                ans.push_back(y);
                freq[y]--;
            }
        }
        return ans;
    }

    // Method 2: Two-Pointer (requires sorted arrays)
    vector<int> intersect_sorted(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        vector<int> ans;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) i++;
            else if (nums1[i] > nums2[j]) j++;
            else {
                ans.push_back(nums1[i]);
                i++; j++;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums1 = {4,9,5};
    vector<int> nums2 = {9,4,9,8,4};

    // Demonstrate both methods
    vector<int> res_map = sol.intersect_map(nums1, nums2);
    vector<int> res_sorted = sol.intersect_sorted(nums1, nums2);

    cout << "Hashmap method result: ";
    for (int x : res_map) cout << x << " ";
    cout << "\n";

    cout << "Sorted two-pointer result: ";
    for (int x : res_sorted) cout << x << " ";
    cout << "\n";
    
    return 0;
}
