#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

template <class TValue>
void print_array(const vector<TValue> &array)
{
    for (auto item : array) {
        cout<<item<<" ";
    }

    cout<<endl;
}

int main()
{
    vector<int> array {10, 1, 7, 5, 2, 2, 5, 8 };

    print_array(array);

    bubble_sort(array);

    print_array(array);

    return 0;
}