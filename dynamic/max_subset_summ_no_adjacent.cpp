#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

int maxSubsetNoAdjacent(vector<int> array)
{
    auto size = array.size();
    if (size == 0) {
        return 0;
    }

    if (size == 1) {
        return array[0];
    }

    vector<int> temp(size);

    temp[0] = array[0];
    temp[1] = max(array[0], array[1]);

    for (auto i = 2; i < size; ++i) {
        temp[i] = max(
            temp[i - 1],
            temp[i - 2] + array[i]
        );
    }

    return temp[size - 1];
}

int main()
{
    // vector<int> array {75, 105, 120, 75, 90, 135};
    vector<int> array {4, 3, 5, 200, 5, 3};

    cout<<"Max summ: "<<maxSubsetNoAdjacent(array)<<endl;

    return 0;
}