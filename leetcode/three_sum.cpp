#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

template <class It>
vector<pair<int, int>> twoSum(It begin, It end, int target)
{
    vector<pair<int, int>> result;
    
    if (distance(begin, end) < 2) {
        return result;
    }
    
    unordered_set<int> previous;
    previous.insert(*begin);
    
    for (It it = begin + 1; it != end; ++it) {
        auto& num = *it;
        int expected = target - num;
        
        if (previous.find(expected) == previous.end()) {
            previous.insert(num);
            continue;
        }
        
        result.push_back({expected, num});
    }
    
    return result;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;

    if (nums.size() < 3) {
        return result;
    }
    
    for (auto it = nums.begin(); it != nums.end() - 2; ++it) {
        auto& num = *it;
        auto pairs = twoSum(it + 1, nums.end(), -num);
        
        for (auto pair : pairs) {
            result.push_back({num, pair.first, pair.second});
        }
    }
    
    return result;
}

void test(vector<int>&& test)
{
    cout<<"Test: { ";
    for (auto item : test) {
        cout<<item<<" ";
    }
    cout<<"}"<<endl;

    auto result = threeSum(test);

    for (auto resultSet : result) {
        cout<<"{"<<resultSet[0]<<", "<<resultSet[1]<<", "<<resultSet[2]<<"}"<<endl;
    }
}

int main()
{
    test({-1, 0, 1, 2, -1, -4});
    test({0, 0, 0, 0});

    return 0;
}