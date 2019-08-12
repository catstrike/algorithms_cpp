#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int lengthOfLongestSubstringTwoDistinct(string s) 
{
    if (s.size() == 0) {
        return 0;
    }

    int left = 0;
    char lastLetter = s[0];
    int lastLetterIndex = 0;
    int result = 1;

    char a = lastLetter;
    char b = lastLetter;

    int i = 1;
    for (; i < s.size(); ++i) {
        const auto& c = s[i];

        if (c == lastLetter) {
            continue;
        }

        auto previousLastLetterIndex = lastLetterIndex;
        auto previousLastLetter = lastLetter;
        lastLetter = c;
        lastLetterIndex = i;

        if (c == a || c == b) {
            continue;
        }

        if (a == b) {
            b = c;
            continue;
        }

        if (i - left > result) {
            result = i - left;
        }

        a = previousLastLetter;
        b = c;
        left = previousLastLetterIndex;
    }

    if (i - left > result) {
        result = i - left;
    }

    return result;
}

int main()
{
    string test01 {"eceba"};
    string test02 {"ccaabbb"};
    string test03 {"cdaba"};

    cout<<test01<<": "<<lengthOfLongestSubstringTwoDistinct(test01)<<endl;
    cout<<test02<<": "<<lengthOfLongestSubstringTwoDistinct(test02)<<endl;
    cout<<test03<<": "<<lengthOfLongestSubstringTwoDistinct(test03)<<endl;

    return 0;
}