// Link to the problem:
// https://leetcode.com/problems/contains-duplicate/description/

// Solution : 
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> st;
        for(int x : nums){
            if(st.count(x)) return true;
            st.insert(x);
        }
        return false;
    }
};

// Learning :
// Use unordered_set instead of set because set uses Red-Black Tree and its avg time complexity for operations is O(logn) compared to O(1) of unordered sets.
// So for existence checks, unordered_set is always your go-to.

// Why do we prefer set sometimes over unordered sets
// When worst-case guarantees matter more than average speed (since set is O(log n) guaranteed, unordered_set can degrade with bad hashing).
// We don’t manually calculate or see the hash code or bucket index.
// C++ does all that automatically behind the scenes using something called a hash function and an internal hash table.
/* 
hash<int> hasher;
size_t hash_value = hasher(37);

size_t is basically an unsigned integer type, usually equivalent to
unsigned long or unsigned long long depending on your system.

This std::hash<T> is a built-in functor (function object) defined in <functional>.
Each type (int, string, etc.) has its own hash logic.

Once it has the hash value, it figures out which bucket this element goes to:
bucket_index = hash_value % bucket_count;
If bucket 5 is empty → store 37 directly.
If bucket 5 already has something (say 21 also went to bucket 5),
then it chains them inside that bucket (like a small linked list or array).

if (st.count(37))
C++ again:
computes hash(37)
finds the bucket (hash % bucket_count)
looks inside that bucket for 37
That’s why average time is O(1) — it knows where to look immediately instead of scanning the entire container.
*/