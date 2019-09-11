#include <iostream>
#include <vector>

using namespace std;

int trap(vector<int>& height) 
{
    if (height.empty()) {
        return 0;
    }

    int left = 0;
    int right = height.size() - 1;

    int maxLeftHeight = height[left];
    int maxRightHeight = height[right];

    int result = 0;

    while (left <= right) {
        if (maxLeftHeight < maxRightHeight) {
            auto& h = height[left];
            maxLeftHeight = max(maxLeftHeight, h);
            result += maxLeftHeight - h;
            left++;
        } else {
            auto& h = height[right];
            maxRightHeight = max(maxRightHeight, h);
            result += maxRightHeight - h;
            right--;
        }
    }

    return result;
}

int main()
{
    vector<int> input {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    cout << "Result = " << trap(input) << endl;

    return 0;
}