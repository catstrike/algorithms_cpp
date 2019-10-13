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

void getSelectedItems(const vector<Item>& items, vector<vector<int>>& table, vector<Item>& result)
{
    if (table.empty()) {
        result = {};
        return;
    }

    auto i = table.size() - 1;
    auto j = table[0].size() - 1;

    while (i > 0 && j > 0) {
        const auto& item = items[i - 1];
        if (table[i][j] == table[i - 1][j - item.weight] + item.value) {
            result.push_back(item);
            j -= item.weight;
        }
        i--;
    }
}

int knapsackMaxValueDynamic(const vector<Item>& items, int availableWeight, vector<Item>& includedItems)
{   
    vector<vector<int>> table(
        items.size() + 1,
        vector<int>(availableWeight + 1)
    );

    for (auto i = 1; i <= items.size(); ++i) {
        const auto& item = items[i - 1];

        for (auto j = 1; j <= availableWeight; ++j) {
            if (j < item.weight) {
                table[i][j] = table[i - 1][j];
                continue;
            }

            table[i][j] = max(
                table[i - 1][j],
                item.value + table[i - 1][j - item.weight]
            );
        }
    }

    getSelectedItems(items, table, includedItems);

    return table[items.size()][availableWeight];
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

    vector<Item> includedItems;
    cout << "Max value (dynamic) = " << knapsackMaxValueDynamic(test_00, maxWeight, includedItems) << endl;

    for (auto& item : includedItems) {
        cout << "{" << item.weight << ", " << item.value << "} ";
    }
    cout << endl;

    return 0;
}