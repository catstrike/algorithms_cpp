#include <iostream>
#include <stack>
#include <climits>

using namespace std;


bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool safeMultiply(int& a, int b) {
    if (INT_MAX / b < a) {
        return false;
    }
    
    a *= b;
    return true;
}

bool safeAdd(int& a, int b) {
    if (INT_MAX - b < a) {
        return false;
    }
    
    a += b;
    
    return true;
}

int fromStack(stack<int>& digits, int sign)
{
    int result = 0;
    int order = 1;
    
    while (!digits.empty()) {
        auto digit = digits.top();
        digits.pop();
        
        if (!safeMultiply(digit, order)) {
            return sign < 0 ? INT_MIN : INT_MAX;
        }
        
        if (!safeAdd(result, digit)) {
            return sign < 0 ? INT_MIN : INT_MAX;
        }
        
        if (digits.empty()) {
            break;
        }
        
        if (!safeMultiply(order, 10)) {
            return sign < 0 ? INT_MIN : INT_MAX;
        };
    }
    
    return result * sign;
}

int myAtoi(string str) {
    auto size = str.size();
    
    // Looking for not ' '
    decltype(size) i = 0;
    for (; i < size; ++i) {
        if (str[i] != ' ') {
            break;
        }
    }
    
    if (i == size) {
        return 0;
    }
    
    // Sign
    int sign = 1;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    } else if (!isDigit(str[i])) {
        return 0;
    }
    
    // Parse number
    stack<int> digits;
    
    for (; i < size; ++i) {
        auto& ch = str[i];
        
        if (!isDigit(ch)) {
            break;
        }
        
        // skip leading zeroes
        if (ch == '0' && digits.empty()) {
            continue;
        }
        
        digits.push(ch - '0');
    }
    
    
    return fromStack(digits, sign);
}

int main()
{
    string test01 = "  0000000000012345678";
    cout << test01 << " -> " << myAtoi(test01) << endl;
}