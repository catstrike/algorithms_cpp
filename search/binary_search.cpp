#include <vector>
#include <iostream>

template <class It, class Value>
It my_binary_search(It first, It last, Value value)
{
    auto count = std::distance(first, last);
    decltype(count) step;
    decltype(first) it;

    while (count > 0) {
        step = count / 2;
        it = first;
        std::advance(it, step);

        if (*it == value) {
            return it;
        }

        if (*it < value) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }

    return last;
}

template <class T>
void binary_search_test(const std::vector<T>& array, T value, long expectedDistance)
{
    auto begin = std::begin(array);
    auto end = std::end(array);
    auto it = my_binary_search(begin, end, value);

    auto index = (it != end)
        ? std::distance(begin, it)
        : -1;

    auto result = index == expectedDistance;

    std::string stringResult = result ? "[+]" : "[-]";
    std::cout << stringResult << " looking for: " << value << ", expected index: " << expectedDistance << ", result: " << index << std::endl;
}

int main()
{
    //                     0  1  2  3  4  5  6  7   8   9 
    std::vector<int> data {1, 2, 3, 4, 5, 6, 8, 10, 14, 17};

    binary_search_test(data, 10, 7);
    binary_search_test(data,  1, 0);
    binary_search_test(data, 17, 9);
    binary_search_test(data,  2, 1);
    binary_search_test(data, 14, 8);
    binary_search_test(data, -5, -1);
    binary_search_test(data, 18, -1);

    auto it = my_binary_search(std::begin(data), std::end(data), 10);

    std::cout << "Value = " << *it << std::endl;

    return 0;
}