#include <iostream>
#include <vector>

using namespace std;

int uniquePaths(int m, int n)
{
    auto rows = m + 1;
    auto columns = n + 1;
    
    vector<vector<int>> table(rows, vector<int>(columns));

    int i = 1;
    int j = 1;

    for (; i < rows; i++) {
        for (; j < columns; j++) {
            table[i][j] = table[i - 1][j] + table[i][j - 1];
        }
    }

    return table[i - 1][j - 1];
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