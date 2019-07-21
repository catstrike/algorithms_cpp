#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int min(int a, int b)
{
    return a < b ? a : b;
}

int minNumberOfCoinsForChange(int n, vector<int> denoms)
{
    vector<int> numberOfCoins(n + 1, INT_MAX);
    numberOfCoins[0] = 0;

    for (auto coin : denoms) {
        for (auto amount = coin; amount <= n; ++amount) {
            auto restCoins = numberOfCoins[amount - coin];

            if (restCoins == INT_MAX) {
                continue;
            }

            numberOfCoins[amount] = min(
                restCoins + 1,
                numberOfCoins[amount]
            );
        }
    }

    auto result = numberOfCoins[n];

    return result == INT_MAX ? -1 : result;
}

int main()
{
    auto result = minNumberOfCoinsForChange(9, {3, 5});

    cout<<"Minimum coins: "<<result<<endl;
}