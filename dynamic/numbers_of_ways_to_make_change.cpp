#include <iostream>
#include <vector>

using namespace std;

int numberOfWaysToMakeChange(int n, vector<int> denoms)
{
    vector<int> ways(n + 1);

    ways[0] = 1;

    for (auto i = 0; i < denoms.size(); ++i) {
        auto coin = denoms[i];

        for (auto j = coin; j <= n; ++j) {
            auto delta = j - coin;
            ways[j] = ways[delta] + ways[j];
        }
    }

    return ways[n];
}

int main()
{
    auto result = numberOfWaysToMakeChange(10, {1, 5, 10, 25});

    cout<<"Result: "<<result<<endl;

    return 0;
}