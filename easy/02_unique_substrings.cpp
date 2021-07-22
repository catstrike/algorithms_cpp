#include <iostream>
#include <vector>
#include <unordered_map>

#include "my_serialization.h"
#include "my_test.h"

std::vector<std::string> unique_substrings(std::string input)
{
    if (input.size() == 0) {
        return {};
    }

    std::unordered_map<char, size_t> rangeMap;

    for (size_t i = 0; i < input.size(); ++i) {
        auto character = input[i];

        rangeMap[character] = i;
    }

    std::vector<std::string> result;

    size_t start = 0;
    size_t endOfRange = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        auto character = input[i];
        auto characterRange = rangeMap[character];

        if (i > endOfRange) {
            result.push_back(
                input.substr(start, endOfRange - start + 1)
            );

            start = i;
            endOfRange = characterRange;
            continue;
        }

        if (endOfRange < characterRange) {
            endOfRange = characterRange;
        }

    }

    result.push_back(
        input.substr(start, start - endOfRange + 1)
    );

    return result;
}

int main()
{
    using Parameter = std::string;
    using Return = std::vector<std::string>;

    my_test(unique_substrings, Return({"abca", "eee", "ffdgfdd"}), Parameter("abcaeeeffdgfdd"));
    my_test(unique_substrings, Return({"a", "b", "c"}), Parameter("abc"));

    return 0;
}