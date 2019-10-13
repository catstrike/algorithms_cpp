#ifndef _HEAP_HEAP_MAP_H_
#define _HEAP_HEAP_MAP_H_

#include <vector>
#include <unordered_map>

// Heap Map
// push():  O(log(n))
// pop():   O(log(n))
// top():   O(1)
// find():  O(1)
// erase(): O(log(n))

template <class MapKey, class HeapKey, class Comparer = std::less<HeapKey>>
class heap_map {
public: // - Public types
    using keys_pair = std::pair<MapKey, HeapKey>;
    using iterator = typename std::vector<keys_pair>::iterator;
    using const_iterator = typename std::vector<keys_pair>::const_iterator;

private: // - State
    std::vector<keys_pair> items;
    std::unordered_map<MapKey, size_t> map;
    Comparer compare;

public: // - Lifecycle
    heap_map() {}
    
    heap_map(const Comparer& compare)
        : compare(compare)
    {}

public: // - Public API
    iterator begin()
    {
        return std::begin(items);
    }

    iterator end()
    {
        return std::end(items);
    }

    size_t size() const
    {
        return items.size();
    }

    bool empty() const
    {
        return items.empty();
    }

    const keys_pair& top() const
    {
        return items[0];
    }

    void push(keys_pair pair)
    {
        size_t itemIndex = items.size();
        items.push_back(pair);
        map.insert({pair.first, itemIndex});

        siftUp(itemIndex);
    }

    void pop()
    {
        erase(0);
    }

    const_iterator find(MapKey mapKey) const
    {
        auto mapIt = map.find(mapKey);
        if (mapIt == std::end(map)) {
            return std::cend(items);
        }

        auto it = std::cbegin(items);
        std::advance(it, mapIt->second);

        return it;
    }

    void erase(const_iterator it)
    {
        auto mapIt = map.find(it->first);
        if (mapIt == std::end(map)) {
            return;
        }

        erase(mapIt->second);
    }

private: // - Internal
    void siftUp(size_t index) {
        while (index > 0) {
            auto parentIndex = getParentIndex(index);
            auto& item = items[index];
            auto& parent = items[parentIndex];

            if (!compare(parent.second, item.second)) {
                return;
            }

            swapItems(parent, item);
            index = parentIndex;
        }
    }

    void siftDown(size_t index) {

        while (true) {
            auto endIndex = size();
            auto leftIndex = getLeftChildIndex(index);
            auto rightIndex = getRightChildIndex(index);
            auto& item = items[index];
            
            size_t candidate = index;

            if (leftIndex < endIndex && compare(item.second, items[leftIndex].second)) {
                candidate = leftIndex;
            }

            if (rightIndex < endIndex && compare(items[candidate].second, items[rightIndex].second)) {
                candidate = rightIndex;
            }

            if (candidate == index) {
                return;
            }

            swapItems(item, items[candidate]);
            index = candidate;
        }
    }

    void erase(size_t index)
    {
        auto& first = items[index];
        auto& last = items[size() - 1];

        auto mapIt = map.find(first.first);

        swapItems(first, last);
        items.pop_back();

        siftDown(index);

        map.erase(mapIt);
    }

    void swapItems(keys_pair& firstItem, keys_pair& secondItem)
    {
        auto firstInMap = map.find(firstItem.first);
        auto secondInMap = map.find(secondItem.first);

        std::swap(firstInMap->second, secondInMap->second);
        std::swap(firstItem, secondItem);
    }

    constexpr size_t getParentIndex(size_t child) {
        return (child - 1) / 2;
    }

    constexpr size_t getLeftChildIndex(size_t parent) {
        return parent * 2 + 1;
    }

    constexpr size_t getRightChildIndex(size_t parent) {
        return parent * 2 + 2;
    }
};

#endif // _HEAP_HEAP_MAP_H_