#include <iostream>
#include <vector>

using namespace std;

int uniquePaths(int m, int n) {
    if (n > m) {
        return uniquePaths(n, m);
    }
    
    vector<vector<int>> table(2, vector<int>(n, 1));
    
    auto previous = &table[0];
    auto current = &table[1];
    
    int i, j;
    
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            (*current)[j] = (*previous)[j] + (*current)[j - 1];
        }
        
        swap(previous, current);
    }
    
    return (*previous)[n - 1];
}

void test(int m, int n, int expected)
{
    auto result = uniquePaths(m, n);
    string resultText = result == expected 
        ? "[+]"
        : "[-]";

    cout << resultText << " uniquePaths(" << m << ", " << n << ") -> " << result << ", expected: " << expected << endl;
}

int main()
{
    test(2, 2, 2);
    test(2, 3, 3);
    test(2, 4, 4);
    test(3, 3, 6);

    return 0;
}