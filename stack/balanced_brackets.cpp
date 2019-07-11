#include <string> // std::string
#include <stack>
#include <iostream> // std::cout

using namespace std;

// Balanced brackets
//
// Time complexity: O(n)
// Space complexity: O(n)

#define IS_OPEN(c) (c == '(' || c == '{' || c == '[')
#define IS_CLOSE(c) (c == ')' || c == '}' || c == ']')
#define SAME_GROUP(o, c) ((o == '(' && c == ')') || (o == '{' && c == '}') || (o == '[' && c == ']'))

bool balancedBrackets(string str) {
    stack<char> stack;

    for (auto c : str) {
        if (IS_OPEN(c)) {
            stack.push(c);
            continue;
        }
        if (IS_CLOSE(c)) {
            if (stack.empty()) {
                return false;
            }
            auto open = stack.top();
            stack.pop();
            if (!SAME_GROUP(open, c)) {
                return false;
            }
        }
    }

    return stack.empty();
}

int main()
{
    string line = "()({{()()}})";

    auto result = balancedBrackets(line);

    cout << line << " is " << (result ? "balanced" : "unbalanced") << endl;

    return 0;
}