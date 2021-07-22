#include <iostream>
#include <array>
#include <unordered_map>

#include "my_test.h"

#define LETTER_INDEX(c) (c - 'a')
#define LETTERS_COUNT ('z' - 'a' + 1)

/*
 * O(n)
 * n = length(text)
 */
class WindowFast
{
    using Counter = std::array<int, LETTERS_COUNT>;

    Counter window;
    Counter pattern;

    std::string text;
    size_t position;
    size_t windowSize;

    unsigned long unfulfilledLetters;

public:
    WindowFast(std::string text, std::string substring)
        : position(substring.size())
        , windowSize(substring.size())
        , text(text)
        , unfulfilledLetters(0)
    {
        window.fill(0);
        pattern.fill(0);

        for (auto c : substring) {
            ++pattern[LETTER_INDEX(c)];

            setUnfulfilledFlag(c);
        }

        for (size_t i = 0; i < windowSize; ++i) {
            char c = text[i];
            ++window[LETTER_INDEX(c)];

            updateFulfilledFlag(c);
        }
    }

    bool moveNext()
    {
        if (position == text.size()) {
            return false;
        }

        auto lastCharacter = text[position - windowSize];
        auto nextCharacter = text[position];

        ++window[LETTER_INDEX(nextCharacter)];
        --window[LETTER_INDEX(lastCharacter)];

        position++;

        updateFulfilledFlag(lastCharacter);
        updateFulfilledFlag(nextCharacter);

        return true;
    }

    bool isFulfilled()
    {
        return unfulfilledLetters == 0;
    }
private:
    void updateFulfilledFlag(char c)
    {
        if (!isLetterOfInterest(c)) return;

        auto index = LETTER_INDEX(c);

        if (window[index] == pattern[index]) {
            setFulfilledFlag(c);
        } else {
            setUnfulfilledFlag(c);
        }


    }
    bool isLetterOfInterest(char c)
    {
        return pattern[LETTER_INDEX(c)] > 0;
    }

    void setFulfilledFlag(char c)
    {
        unfulfilledLetters &= ~(1ul << LETTER_INDEX(c));
    }

    void setUnfulfilledFlag(char c)
    {
        unfulfilledLetters |= 1ul << LETTER_INDEX(c);
    }
};

/*
 * O(n*a)
 * n = length(text)
 * a = alphabet size
 */
class Window
{
    using Counter = std::unordered_map<char, int>;

    Counter window;
    Counter pattern;

    std::string text;
    size_t position;
    size_t windowSize;

public:
    Window(std::string text, std::string substring)
        : position(substring.size())
        , windowSize(substring.size())
        , text(text)
    {
        for (auto c : substring) {
            ++pattern[c];
        }

        for (size_t i = 0; i < windowSize; ++i) {
            ++window[text[i]];
        }
    }

    bool moveNext()
    {
        if (position == text.size()) {
            return false;
        }

        auto lastCharacter = text[position - windowSize];
        auto nextCharacter = text[position];

        ++window[nextCharacter];
        --window[lastCharacter];

        position++;

        return true;
    }

    bool isFulfilled()
    {
        for (auto pair : pattern) {
            if (window[pair.first] != pair.second) {
                return false;
            }
        }

        return true;
    }
};

bool find_unordered_substring(std::string text, std::string substring)
{
    if (text.size() < substring.size()) {
        return false;
    }

    WindowFast window(text, substring);

    while (!window.isFulfilled() && window.moveNext());

    return window.isFulfilled();
}

int main()
{
    my_test(find_unordered_substring, true, std::string("adbabc"), std::string("abb"));
    my_test(find_unordered_substring, false, std::string("abdabc"), std::string("abb"));
    my_test(find_unordered_substring, false, std::string("abdabc"), std::string("dbc"));
    my_test(find_unordered_substring, true, std::string("abdabc"), std::string("db"));
    my_test(find_unordered_substring, true, std::string("abdabc"), std::string("cb"));
    my_test(find_unordered_substring, true, std::string("abdabc"), std::string("dba"));

    return 0;
}