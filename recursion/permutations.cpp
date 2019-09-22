#include <vector>
#include <iostream>

using namespace std;

template <class ItemType>
void permutations(int partition, vector<ItemType>& items, vector<vector<ItemType>>& result)
{
    if (partition == items.size() - 1) {
        result.push_back(items);
        return;
    }

    for (int i = partition; i < items.size(); ++i) {
        swap(items[i], items[partition]);
        permutations(partition + 1, items, result);
        swap(items[i], items[partition]);
    }
}

template <class ItemType>
void permutations(vector<ItemType>& items, vector<vector<ItemType>>& result)
{
    permutations(0, items, result);
}

template<class It>
void printCollection(It begin, It end)
{
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> items {1, 2, 3};
    vector<vector<int>> result;

    permutations(items, result);

    for (auto& permutation : result) {
        printCollection(permutation.begin(), permutation.end());
    }

    return 0;
}