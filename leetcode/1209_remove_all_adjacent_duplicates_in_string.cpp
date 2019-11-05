#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

struct Item {
    char value;
    size_t count;
};

string removeDuplicates(string input, int k) {
    if (input.empty()) {
        return input;
    }

    stack<Item> s;

    for (auto ch : input) {
        if (s.empty() || s.top().value != ch) {
            s.push({ch, 1});
            continue;
        }

        auto& count = s.top().count;
        count++;

        if (count == k) {
            s.pop();
        }
    }

    stringstream ss;

    for (int i = s.size() - 1; !s.empty(); --i) {
        auto& item = s.top();

        ss << string(item.count, item.value);
        s.pop();
    }

    string result = ss.str();
    reverse(begin(result), end(result));

    return result;
}

void test(string text, int k, string expected)
{
    auto result = removeDuplicates(text, k);
    string resultText = result == expected 
        ? "[+]"
        : "[-]";

    cout << resultText << " " << text << " -> " << result << ", expected " << expected << endl;
}

int main()
{
    test("abcd", 2, "abcd");
    test("deeedbbcccbdaa", 3, "aa");
    test("pbbcggttciiippooaais", 2, "ps");
}