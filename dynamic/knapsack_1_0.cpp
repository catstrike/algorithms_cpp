#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight;
    int value;
};

template <class Iterator>
constexpr
int knapsackMaxValue(Iterator begin, Iterator end, int availableWeight)
{
    if (begin == end || availableWeight == 0) {
        return 0;
    }

    if (begin->weight > availableWeight) {
        return knapsackMaxValue(begin + 1, end, availableWeight);
    }

    return max(
        knapsackMaxValue(begin + 1, end, availableWeight - begin->weight) + begin->value,
        knapsackMaxValue(begin + 1, end, availableWeight)
    );
}

int knapsackMaxValueDynamic(const vector<Item>& items, int availableWeight)
{   
    vector<vector<int>> cache(
        items.size() + 1,
        vector<int>(availableWeight + 1)
    );

    for (int i = 1; i <= items.size(); ++i) {
        for (int j = 1; j <= availableWeight; ++j) {
            auto& item = items[i - 1];
            auto& currentCache = cache[i][j];
            auto& previous = cache[i - 1][j];

            if (item.weight > j) {
                currentCache = previous;
                continue;
            }

            currentCache = max(
                previous,
                cache[i - 1][j - item.weight] + item.value
            );
        }
    }

    return cache[items.size()][availableWeight];
}

int main()
{
    int maxWeight = 5;

    vector<Item> test_00 = {
        {1, 10},
        {3, 12},
        {2, 15},
        {4, 20}
    };

    cout << "Max value = " << knapsackMaxValue(test_00.begin(), test_00.end(), maxWeight) << endl;
    cout << "Max value (dynamic) = " << knapsackMaxValueDynamic(test_00, maxWeight) << endl;

    return 0;
}