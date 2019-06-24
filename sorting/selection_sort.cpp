#include <vector> // std::vector
#include <algorithm> // std::swap

#include "shared.h"

using namespace std;

// Selection Sort
//
// Time complexity:
//   best case:    O(n^2)
//   average case: O(n^2)
//   worst case:   O(n^2)
//
// Space complexity
//   O(1)

template<class TValue>
void selection_sort(vector<TValue>& array)
{
    auto size = array.size();

    for (auto i = 0; i < size; ++i) {
        auto smallest_index = i;
        for (auto j = i + 1; j < size; ++j) {
            if (array[j] < array[smallest_index]) {
                smallest_index = j;
            }
        }
        swap(array[i], array[smallest_index]);
    }
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };

    print_array(array);
    selection_sort(array);
    print_array(array);

    return 0;
}