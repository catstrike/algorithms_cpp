#include <iostream>

using namespace std;

int equalSubstring(string s, string t, int maxCost)
{
    auto size = s.size();

    if (size == 0) {
        return 0;
    }

    int left = 0;
    int right = 0;
    int maxLength = 0;
    int sum = 0;

    for (; right < size; right++) {
        auto value = abs(s[right] - t[right]);

        sum += value;

        if (sum <= maxCost) {
            continue;
        }

        maxLength = max(maxLength, right - left);

        while (sum > maxCost) {
            sum -= abs(s[left] - t[left]);
            left++;
        }
    }

    if (sum <= maxCost) {
        maxLength = max(maxLength, right - left);
    }

    return maxLength;
}

void test(string a, string b, int maxCost, int expected)
{
    auto result = equalSubstring(a, b, maxCost);
    string resultText = result == expected 
        ? "[+]"
        : "[-]";

    cout << resultText << " " << a << " : " << b << " -> " << result << ", expected " << expected << endl;
}

int main()
{
    test("abcd", "bcdf", 3, 3);
    test("abcd", "cdef", 3, 1);
    test("abcd", "acde", 0, 1);
    test("abcd", "zzzz", 9, 0);
    test("abcd", "abcd", 0, 4);

    return 0;
}