// 🔗 Problem Link:
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
//
// 🧠 Problem Summary:
// You are given an array 'prices' where prices[i] is the stock price on day i.
// You can only complete ONE transaction (buy one and sell one share).
// Return the maximum profit possible. If no profit can be made, return 0.
//
// Example:
// Input: prices = [7,1,5,3,6,4]
// Output: 5
// Explanation: Buy on day 2 (price=1), sell on day 5 (price=6), profit = 6-1=5.
//
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buyingPrice = 0;      // pointer for the best day to buy
        int sellingPrice = 1;     // pointer for the day we're considering selling
        int maxProfit = 0;        // track the best profit so far

        while (sellingPrice < prices.size()) {
            // If current selling price is smaller, update buying pointer
            if (prices[sellingPrice] < prices[buyingPrice]) {
                buyingPrice = sellingPrice;
            } else {
                // Calculate profit if we sell at current price
                int profit = prices[sellingPrice] - prices[buyingPrice];
                maxProfit = max(maxProfit, profit);
            }
            sellingPrice++;
        }

        return maxProfit;
    }
};

// ---------------------------------------------------------------------------
// 💡 Intuition:
// ---------------------------------------------------------------------------
/*
We need to buy at the lowest price before a higher selling price appears.

We can visualize this as:
   - Move selling pointer forward each day.
   - Keep track of the minimum price so far (best buying day).
   - Calculate profit = prices[selling] - prices[buying].
   - Update maxProfit whenever we find a better profit.

This is a perfect two-pointer "expanding window" problem.
*/

// ---------------------------------------------------------------------------
// 🧩 Example Dry Run:
// ---------------------------------------------------------------------------
/*
prices = [7, 1, 5, 3, 6, 4]

buy=0 (7), sell=1 (1)
  → prices[sell] < prices[buy] → move buy=1
buy=1 (1), sell=2 (5)
  → profit = 5 - 1 = 4, maxProfit=4
buy=1 (1), sell=3 (3)
  → profit = 3 - 1 = 2
buy=1 (1), sell=4 (6)
  → profit = 6 - 1 = 5 ✅ maxProfit=5
buy=1 (1), sell=5 (4)
  → profit = 4 - 1 = 3

✅ Final Answer = 5
*/

// ---------------------------------------------------------------------------
// ⚙️ Complexity Analysis:
// ---------------------------------------------------------------------------
/*
Time  → O(n)
Space → O(1)
*/

// ---------------------------------------------------------------------------
// 🧠 Learnings Recap:
// ---------------------------------------------------------------------------
/*
✅ This problem is a greedy sliding-window pattern:
   - Maintain a "buy pointer" at the lowest price.
   - Slide "sell pointer" to find best profit.

✅ When to reset your window?
   When a new smaller price appears → reset buying pointer.

✅ Pattern unlocked:
   "Maintain min/max value while traversing once" → works for:
      - Max Profit problems
      - Temperature spans
      - Maximum difference problems
*/
// ---------------------------------------------------------------------------

// 🎯 Takeaway:
// Don’t brute force every pair of buy-sell days (O(n²)).
// Just keep track of the smallest price so far and maximize profit in one pass.
// ---------------------------------------------------------------------------

