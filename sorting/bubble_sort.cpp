#include <vector> // std::vector
#include <algorithm> // std::swap

#include "array_utility.h" // print_array

using namespace std;

// Bubble Sort
//
// Time complexity:
//   best case:    O(n)
//   average case: O(n^2)
//   worst case:   O(n^2)
//
// Space complexity
//   O(1)

template <class TValue>
void bubble_sort(vector<TValue> &array)
{
    auto size = array.size();

    for (auto i = 0; i < size; ++i) {
        bool sorted = true;
        for (auto j = 1; j < size - i; ++j) {
            if (array[j - 1] > array[j]) {
                swap(array[j - 1], array[j]);
                sorted = false;
            }
        }

        if (sorted) {
            break;
        }
    }
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };
    
    print_array(array);
    bubble_sort(array);
    print_array(array);

    return 0;
}