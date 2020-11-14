#include <iostream>
#include <vector>

using namespace std;

#define AlphabetSize ('z' - 'a' + 1)
#define alphabetLetter(i) ('a' + i)

int alphabet(string input)
{
    auto rows = AlphabetSize + 1;
    auto columns = input.size() + 1;

    vector<vector<int>> table(rows, vector<int>(columns));

    for (int i = 0; i < rows; i++) {
        table[i][0] = i;
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            auto& target = table[i][j];

            if (input[j - 1] == alphabetLetter(i - 1)) {
                target = table[i - 1][j - 1];
                continue;
            }

            auto insert = table[i - 1][j] + 1;
            auto remove = table[i][j - 1];

            target = min(insert, remove);
        }
    }

    return table[rows - 1][columns - 1];
}

int main()
{
    string input;
    int expected;

    cin>>input>>expected;

    int result = alphabet(input);
    string stringResult = result == expected ? "[+]" : "[-]";

    cout<<stringResult<<" Input: "<<input<<", expected: "<<expected<<", result: "<<result<<endl;
}