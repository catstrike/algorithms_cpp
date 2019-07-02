#include <vector> // std::vector
#include <algorithm> // std::swap

#include "shared.h" // print_array

using namespace std;

template<class Iterator>
Iterator partition(Iterator left, Iterator right)
{
    if (left >= right) {
        return right;
    }

    auto pivot = left;
    ++left;
    --right;

    while (left <= right) {
        if (*left > *pivot && *right < *pivot) {
            swap(*left, *right);
        }

        if (*left <= *pivot) {
            ++left;
        }
        if (*right > *pivot) {
            --right;
        }
    }

    swap(*pivot, *right);

    return right;
}

template<class Iterator>
void quick_sort(Iterator left, Iterator right)
{
    if (distance(left, right) <= 1) {
        return;
    }

    auto pivot = partition(left, right);
    quick_sort(left, pivot);
    quick_sort(pivot + 1, right);
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };

    print_array(array);
    quick_sort(array.begin(), array.end());
    print_array(array);

    return 0;
}
