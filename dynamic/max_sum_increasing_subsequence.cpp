#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> maxSumIncreasingSubsequence(vector<int> array) 
{
    auto size = array.size();

    if (size == 0) {
        return {{0}, {}};
    }

    vector<int> sum(size);
    vector<int> reference(size, -1);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            
        }
    }

    return {{41}, {11, 30}};
}

template <class It>
string join(It begin, It end, string separator)
{
    if (begin == end) {
        return "";
    }

    It it = begin;
    stringstream ss;

    ss << *it; 
    ++it;

    for (; it != end; ++it) {
        ss << separator << *it;
    }

    return ss.str();
}

void test(vector<int> array, int expected, vector<int> expected2)
{
    auto result = maxSumIncreasingSubsequence(array);
    auto sum = result[0][0];
    auto resultArray = result[1];

    auto correct = sum == expected && resultArray == expected2;

    auto resultString = correct ? "[+]" : "[-]";

    cout << resultString << " [" <<
        join(begin(array), end(array), ", ") << "] -> " << sum << ": [" <<
        join(begin(resultArray), end(resultArray), ", ") << "]" << endl;
        
}


int main()
{
    test({10, 70, 20, 30, 50, 11, 30}, 110, {10, 20, 30, 50});

    return 0;
}