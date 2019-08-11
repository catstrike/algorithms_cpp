#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) 
{
    if (height.size() < 2) {
        return 0;
    }

    int result = 0;

    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        auto& leftHeight = height[left];
        auto& rightHeight = height[right];
        auto targetHeight = min(leftHeight, rightHeight);
        auto square = targetHeight * (right - left);

        if (result < square) {
            result = square;
        }

        if (leftHeight < rightHeight) {
            left++;
        } else {
            right--;
        }
    }

    return result;
}

int main()
{
    vector<int> test {1,8,6,2,5,4,8,3,7};

    cout<<maxArea(test)<<endl;

    return 0;
}