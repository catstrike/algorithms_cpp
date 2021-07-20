#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <sstream>

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

std::string serialize_input(std::string input)
{
    return input;
}

std::string serialize_result(std::vector<std::string> result)
{
    std::stringstream ss;

    ss << "[";

    if (result.size() > 0) {
        ss << result[0];
    }

    for (size_t i = 1; i < result.size(); ++i) {
        ss << ", " << result[i];
    }

    ss << "]";

    return ss.str();
}


template <class TypeInput, class TypeExpected>
struct TestCase {
    TypeInput input;
    TypeExpected expected;
};

template <class TypeInput, class TypeExpected>
void test(std::function<TypeExpected(TypeInput)> method, TestCase<TypeInput, TypeExpected> testCase)
{
    TypeExpected result = method(testCase.input);

    bool testResult = result == testCase.expected;
    std::string plusMinus = testResult ? "[+]" : "[-]";

    std::cout << plusMinus
        << " solve(" << serialize_input(testCase.input) << ") -> " << serialize_result(result)
        << ", expected: " << serialize_result(testCase.expected) << std::endl; 
}

int main()
{
    using Input = std::string;
    using Output = std::vector<std::string>;

    TestCase<Input, Output> testCases[] = {
        {"abcaeeeffdgfdd", {"abca", "eee", "ffdgfdd"}},
        {"abc", {"a", "b", "c"}}
    };

    for (auto testCase : testCases) {
        test<Input, Output>(unique_substrings, testCase);
    }

    return 0;
}