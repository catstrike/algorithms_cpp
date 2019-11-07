#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

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

    It it = begin;
    advance(it, 1);
    
    for (; it != end; ++it) {
        auto& num = *it;
        int expected = target - num;
        
        if (previous.find(expected) == std::end(previous)) {
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
    
    for (auto it = begin(nums); it != end(nums) - 2; ++it) {
        auto& num = *it;
        auto pairs = twoSum(it + 1, end(nums), -num);
        
        for (auto pair : pairs) {
            vector<int> solution{num, pair.first, pair.second};
            sort(begin(solution), end(solution));

            if (find(begin(result), end(result), solution) != end(result)) {
                continue;
            }

            result.push_back(solution);
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