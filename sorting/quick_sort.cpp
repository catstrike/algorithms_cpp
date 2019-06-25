#include <vector> // std::vector
#include <algorithm> // std::swap

#include "shared.h" // print_array

using namespace std;

template<class TValue>
void quick_sort(vector<TValue>& array, size_t left, size_t right)
{
    auto size = right - left + 1;

    if (size <= 1) {
        return;
    }
}

template<class TValue>
void quick_sort(vector<TValue>& array)
{
    quick_sort(array, 0, array.size() - 1);
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };

    print_array(array);
    quick_sort(array);
    print_array(array);

    return 0;
}