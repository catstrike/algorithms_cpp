#include <iostream>
#include <vector>

using namespace std;

constexpr size_t charToIndex(char c) {
    return c - 'a';
}

#define getBudget(letters, c) letters[charToIndex(c)]

int maxRepOpt1(string text) {
    if (text.empty()) {
        return 0;
    }

    const int totalLetters = 'z' - 'a' + 1;

    vector<int> letters(totalLetters);

    for (auto c : text) {
        letters[charToIndex(c)]++;
    }

    char currentChar = text[0];
    int budget = getBudget(letters, currentChar);
    int replacementBudget = 1;
    int length = 1;
    int maxLength = 1;
    size_t it = 1;
    size_t returnIt = 0;

    for (; it < text.size(); ++it) {
        auto inBudget = budget - length > 0;

        if (inBudget && text[it] == currentChar) {
            length++;
            continue;
        }

        if (inBudget && replacementBudget > 0) {
            replacementBudget--;
            returnIt = it;
            length++;
            continue;
        }

        maxLength = max(length, maxLength);

        it = returnIt;
        returnIt = it+1;
        currentChar = text[it];
        budget = getBudget(letters, currentChar);
        replacementBudget = 1;
        length = 1;
    }

    return max(maxLength, length);
}

void test(string text, int expected)
{
    auto result = maxRepOpt1(text);
    string resultText = result == expected 
        ? "[+]"
        : "[-]";

    cout << resultText << " " << text << " -> " << result << ", expected " << expected << endl;
}

int main()
{
    test("ababa", 3);
    test("aaabaaa", 6);
    test("aaabbaaa", 4);
    test("aaaaa", 5);
    test("abcdef", 1);
    return 0;
}