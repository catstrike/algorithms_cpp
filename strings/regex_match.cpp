#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Test {
    string text;
    string pattern;
    bool expected;
};

template <class TIterator>
bool match_internal(TIterator textCurrent, TIterator textEnd, TIterator patternCurrent, TIterator patternEnd)
{
    if (textCurrent == textEnd && patternCurrent == patternEnd) {
        return true;
    } else if (textCurrent == textEnd || patternCurrent == patternEnd) {
        return false;
    }

    auto nextPattern = patternCurrent + 1;

    if (nextPattern != patternEnd && *nextPattern == '*') {
        patternCurrent = nextPattern;
    }

    switch(*patternCurrent) {
        case '*': {
            auto patternPrevious = patternCurrent - 1;
            if (*patternPrevious != '.' && *patternPrevious != *textCurrent) {
                return match_internal(textCurrent + 1, textEnd, patternCurrent + 1, patternEnd);
            }

            return match_internal(textCurrent + 1, textEnd, patternCurrent, patternEnd) || 
                match_internal(textCurrent + 1, textEnd, patternCurrent + 1, patternEnd);
        }
        default:
            if (*patternCurrent != *patternCurrent) {
                return false;
            }
        case '.':
            return match_internal(textCurrent + 1, textEnd, patternCurrent + 1, patternEnd);
    }
}

bool match(string text, string pattern)
{
    return match_internal(
        text.cbegin(), text.cend(),
        pattern.cbegin(), pattern.cend()
    );
}

int main()
{
    vector<Test> tests {
        {"aba", "ab", false},
        {"abcd", "abcd", true},
        {"aa", "a*", true},
        {"ab", ".*", true},
        {"ab", ".", false},
        {"aab", "c*a*b", true},
        {"aaa", "a*.", true}
    };

    for (const auto& test : tests) {
        auto result = match(test.text, test.pattern);
        cout<<test.text<<" ("<<test.pattern<<") result: "<<result<<", expected: "<<test.expected<<endl;
    }

    return 0;
}