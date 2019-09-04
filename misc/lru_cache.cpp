#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
    using ItemsType = list<pair<int, int>>;

    ItemsType items;
    unordered_map<int, ItemsType::iterator>  itemsMap;
    int capacity;
    int size;
public:
    LRUCache(int capacity)
        : capacity(capacity)
        , itemsMap(capacity)
        , size(0)
    {
    }
    
    int get(int key) 
    {
        auto it = itemsMap.find(key);

        if (it == itemsMap.end()) {
            return -1;
        }

        it->second = makeItemFirst(it->second);

        return (*it->second).second;
    }
    
    void put(int key, int value) 
    {
        auto it = itemsMap.find(key);

        if (it != itemsMap.end()) {
            it->second = makeItemFirst(it->second);
            it->second->second = value;
        } else {
            auto listIt = items.insert(items.begin(), {key, value});
            itemsMap.insert({key, listIt});
        }

        if (items.size() > capacity) {
            auto keyValue = items.back();            
            itemsMap.erase(keyValue.first);
            items.pop_back();
        }
    }

private:
    ItemsType::iterator makeItemFirst(ItemsType::iterator listIt)
    {
        auto keyValue = *listIt;
        items.erase(listIt);

        return items.insert(items.begin(), keyValue);
    }
};

int main()
{
    return 0;
}