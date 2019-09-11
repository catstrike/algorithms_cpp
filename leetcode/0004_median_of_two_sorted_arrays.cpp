#include <iostream>
#include <vector>
#include <climits>

using namespace std;

double median_of_two_sorted_arrays(vector<int>& first, vector<int>& second)
{
    if (first.empty() && second.empty()) {
        return 0;
    }

    int firstSize = first.size();
    int secondSize = second.size();

    int middle = (firstSize + secondSize + 1) / 2;

    if (first.empty()) {
        return second[middle];
    }

    if (second.empty()) {
        return first[middle];
    }

    if (firstSize < secondSize) {
        return median_of_two_sorted_arrays(second, first);
    }

    int low = middle - min(middle, secondSize);
    int high = middle;

    cout << "low = " << low << " high = " << high << endl;

    while (low < high) {
        int firstContributes = low + (high - low) / 2;
        int secondContributes = middle - firstContributes;

        // int[][2] middleElements = {
        //     {firstContributes > 0 ? first[firstContributes - 1] : MIN_INT, first[firstContribbutes]},
        //     {secondContributes > 0

        //     }
        // };
    }

    return 0;
}

int main()
{
    vector<int> first { 1, 2, 7, 8};
    vector<int> second { 2, 5, 6};

    auto result = median_of_two_sorted_arrays(first, second);

    cout << result << endl;

    return 0;
}