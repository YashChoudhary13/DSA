#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int>nums;
    for (int i = 0 ; i < n  ; i++){
        int x;
        cin >> x;
        nums.push_back(x);
    }

    map <int, int> mp;
    for (int j = 0 ; j < n ; j++){
        int x = nums[j];
        mp[x]++;
    }
    for (auto x: mp){
        cout << x.first << " " << x.second << endl;
    }
    return 0;
}