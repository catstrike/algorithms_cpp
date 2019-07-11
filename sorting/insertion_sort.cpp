#include <vector> // std::vector
#include <algorithm> // std::swap

#include "array_utility.h" // print_array

using namespace std;

// Insertion Sort
//
// Time complexity:
//   best case:    O(n)
//   average case: O(n^2)
//   worst case:   O(n^2)
//
// Space complexity
//   O(1)

template <class TValue>
void insertion_sort(vector<TValue>& array)
{
    auto size = array.size();

    for (auto i = 1; i < size; ++i) {
        for (auto j = i; j > 0 && array[j] < array[j - 1]; --j) {
            swap(array[j], array[j-1]);
        }
    }
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };

    print_array(array);
    insertion_sort(array);
    print_array(array);

    return 0;
}
