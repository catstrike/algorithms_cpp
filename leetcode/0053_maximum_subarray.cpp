#include <iostream>
#include <vector>

using namespace std;

int maxSubArray(vector<int>& nums) 
{
    if (nums.empty()) {
        return 0; // ???
    }

    int result = nums[0];
    auto previous = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        auto current = nums[i] + (previous < 0 ? 0 : previous);
        result = max(current, result);
        previous = current;
    }

    return result;
}

int main()
{
    vector<int> input {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "Result: " << maxSubArray(input) << endl;

    return 0;
}