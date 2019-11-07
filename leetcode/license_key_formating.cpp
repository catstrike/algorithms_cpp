#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stack>
#include <memory>

using namespace std;

string licenseKeyFormatting(string S, int K) {
    
    stack<string> strings;
    
    auto buffer = make_unique<char[]>(K+1);
    int i = S.size() - 1;
    
    buffer[K] = 0;
    
    do {
        auto k = K;
        while (k > 0 && i >= 0) {
            auto c = S[i--];
            if (c == '-') {
                continue;
            }
            
            k--;
            buffer[k] = toupper(c);
        }
        strings.push(&buffer[k]);
    } while (i >= 0);
    
    stringstream result;
    
    while(!strings.empty()) {
        result<<strings.top();
        strings.pop();
        
        if (!strings.empty()) {
            result<<"-";
        }
    }
    
    return result.str();
}

int main()
{
    cout<<licenseKeyFormatting("2-4A0r7-4k", 3)<<endl;
}