// Link to the problem:
// https://leetcode.com/problems/squares-of-a-sorted-array/description/

// Solution:
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        vector<int> ans(n);
        int pos = n - 1;

        while (left <= right) {
            if (abs(nums[left]) > abs(nums[right])) {
                ans[pos--] = nums[left] * nums[left];
                left++;
            } else {
                ans[pos--] = nums[right] * nums[right];
                right--;
            }
        }
        return ans;
    }
};

// Learnings & Key Points:
/*
👉 Concept: Two Pointers from Both Ends
   - Array is sorted, so largest absolute values are at the ends.
   - Square both ends, and whichever is larger gets placed at the back of result.
   - Move that pointer inward and continue.

👉 Intuition I Had:
   - Realized negatives can produce large squares (e.g., -7 → 49)
   - Instead of sorting squared values again (O(n log n)),
     I used two-pointer logic to fill result directly in sorted order.
   - Knew array is sorted in non-decreasing order → extremes matter most.

👉 What Could Go Wrong / Mistakes Avoided:
   - ❌ Sorting after squaring (O(n log n)) — not optimal.
   - ❌ Forgetting to fill from end of result array — would reverse order.
   - ✅ Used `abs()` properly for comparison.
   - ✅ Used `pos = n - 1` to fill largest to smallest from right → left.
   - ✅ Maintained clear pointer movement (left++, right--).

👉 Correct Intuition Flow:
   1️⃣ Initialize two pointers — left (0) and right (n-1).
   2️⃣ Compare |nums[left]| and |nums[right]|.
   3️⃣ Place larger square at ans[pos], decrement pos.
   4️⃣ Move pointer of used element inward.
   5️⃣ Continue until left > right.

👉 Example walkthrough:
   nums = [-4, -1, 0, 3, 10]
   left=0, right=4 → max(|-4|, |10|) = 10 → place 100 → pos=4
   left=0, right=3 → max(|-4|, |3|) = 4 → place 16 → pos=3
   left=1, right=3 → max(|-1|, |3|) = 3 → place 9  → pos=2
   left=1, right=2 → max(|-1|, |0|) = 1 → place 1  → pos=1
   left=2, right=2 → place 0 → pos=0
   ✅ ans = [0,1,9,16,100]

👉 Time & Space:
   - Time Complexity: O(n)
   - Space Complexity: O(n) (can’t be done cleanly in-place)

👉 What I Learned:
   ✅ When array is sorted but transformation changes order (like squaring negatives),
       use **two pointers** to rebuild sorted order efficiently.
   ✅ Always think: “Can I avoid sorting by leveraging the array’s structure?”
   ✅ Pattern reappears in problems like:
        - Two Sum II (Sorted)
        - 3Sum Closest
        - Container With Most Water
        - Merge Sorted Arrays
*/

// Key Takeaways:
/*
✅ Use two pointers when transformation disrupts sorted order.
✅ Fill result array from the back when placing largest elements first.
✅ Compare using absolute values before squaring.
✅ Linear O(n) logic beats any sorting-based approach here.
✅ A clean, must-know array problem that tests both observation and implementation skill.
*/