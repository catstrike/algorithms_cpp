#include <iostream>
#include <vector>
#include <sstream>

template <class Iterator>
int measure_subarray(Iterator& it, Iterator end)
{
    int size = 0;

    for (; it != end && *it == 1; ++it) {
        size++;
    }

    it--;

    return size;
}

template <class Iterator>
int longest_subarray_if_remove_one_item(Iterator begin, Iterator end)
{
    int maxSize = 0;
    int lastArraySize = 0;
    int gap = 0;

    for (auto it = begin; it != end; ++it) {
        if (*it != 1) {
            gap++;
            continue;
        }

        auto size = measure_subarray(it, end);
        auto potentialArraySize = gap == 1
            ? size + lastArraySize
            : size;

        lastArraySize = size;
        gap = 0;

        if (potentialArraySize > maxSize) {
            maxSize = potentialArraySize;
        }
    }

    return maxSize;
}

template <class Iterator>
std::string to_string(Iterator it, Iterator end)
{
    std::stringstream ss;

    if (it != end) {
        ss << *it;
        ++it;
    }

    for (; it != end; ++it) {
        ss << ", " << *it;
    }

    return ss.str();
}

void test(const std::vector<int>& data, int expected)
{
    auto result = longest_subarray_if_remove_one_item(
        std::cbegin(data),
        std::cend(data)
    );

    auto resultText = result == expected
        ? "[+]"
        : "[-]";

    std::cout << resultText 
        << " [" << to_string(std::cbegin(data), std::cend(data)) << "] "
        << "expected: " << expected << ", result: " << result
        << std::endl;
}

int main()
{
    std::vector<int> test1 {0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1};
    std::vector<int> test2 {0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0};
    std::vector<int> test3 {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0};
    std::vector<int> test4 {1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0};

    test(test1, 6);
    test(test2, 4);
    test(test3, 5);
    test(test4, 3);
    
    return 0;
}