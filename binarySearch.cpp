//Binary Search is based on concept of Divide and Conquer


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int target;
    cout<<"Enter the target value: "<<endl;
    cin>>target;
    vector <int> nums = {51, 48, 9, 19, 10, 5};
    sort(nums.begin() , nums.end());
    int n = nums.size();
    int i = 0;
    int j = n - 1;
    while ( i <= j){
        int mid = i + (j-i)/2;
        if(nums[mid] == target){
            cout << "The element is present at index: " << mid <<endl;
            break;
        } else {
            if (target < mid){
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
        cout << "Element is not present in the array" << endl;
    }
}