#ifndef _HEAP_MIN_HEAP_H_
#define _HEAP_MIN_HEAP_H_

#include <vector>
#include <algorithm>

template <class TKey, class TValue>
class MinHeap
{
    struct Item;

    std::vector<Item> items;
public: // - Properties
    bool empty() const
    {
        return items.empty();
    }

    auto size() const
    {
        return items.size();
    }

public: // - Public methods
    void insert(TKey key, TValue value)
    {
        auto index = items.size();
        items.push_back({key, value});

        for (; index > 0;) {
            auto parentIndex = getParentIndex(index);
            auto& parent = items[parentIndex];

            if (parent.key <= key) {
                break;
            }

            std::swap(parent, items[index]);
            index = parentIndex;
        }
    }

    Item extract()
    {
        auto lastIndex = items.size() - 1;
        Item result = items[0];
        items[0] = items[lastIndex];
        items.pop_back();

        for (size_t index = 0; index < lastIndex;) {
            auto leftIndex = getLeftIndex(index);
            auto rightIndex = getRightIndex(index);
            auto smallest = index;

            if (leftIndex < lastIndex && items[leftIndex].key < items[smallest].key) {
                smallest = leftIndex;
            }
            if (rightIndex < lastIndex && items[rightIndex].key < items[smallest].key) {
                smallest = rightIndex;
            }

            if (smallest == index) {
                break;
            }

            std::swap(items[index], items[smallest]);
            index = smallest;
        }

        return result;
    }

    const Item & peek() const
    {
        return items[0];
    }

private: // - Private methods
    size_t getParentIndex(size_t index)
    {
        return (index - 1) / 2;
    }

    size_t getLeftIndex(size_t index)
    {
        return index * 2 + 1;
    }

    size_t getRightIndex(size_t index)
    {
        return index * 2 + 2;
    }
};

template <class TKey, class TValue>
struct MinHeap<TKey, TValue>::Item {
    TKey key;
    TValue value;
};

#endif // _HEAP_MIN_HEAP_H_
