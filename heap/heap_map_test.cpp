#include <iostream>
#include <sstream>

#include "heap_map.h"

using namespace std;

template <class PairType>
string pairToString(PairType pair)
{
    stringstream ss;

    ss << "{" << pair.first << ", " << pair.second << "}";
    return ss.str();
}

template <class HeapType>
void printHeap(HeapType& heap)
{
    for (auto& item : heap) {
        cout << pairToString(item) << " ";
    }
    cout << endl;
}

template <class HeapType>
void printItem(HeapType& heap, size_t index)
{
    auto it = heap.find(index);
    cout << "heap[" << index << "] = " << (it == end(heap) ? "Not Found" : pairToString(*it)) << endl;
}

int main()
{
    heap_map<int, int> heap;

    heap.push({0, 20});
    heap.push({1, 15});
    heap.push({2, 22});
    heap.push({3, 7});

    printHeap(heap);
    cout << "size = " << heap.size() << endl;
    cout << "top = " << pairToString(heap.top()) << endl;

    cout << "heap.erase([2])" << endl;
    auto it = heap.find(2);
    heap.erase(it);

    printItem(heap, 1);
    printItem(heap, 2);
    printItem(heap, 3);
    printItem(heap, 10);
    cout << endl;

    cout << "heap.pop()" << endl;
    heap.pop();
    cout << "size = " << heap.size() << endl;
    cout << "top = " << pairToString(heap.top()) << endl;
    printHeap(heap);
    cout << endl;

    cout << "heap.pop()" << endl;
    heap.pop();
    cout << "size = " << heap.size() << endl;
    cout << "top = " << pairToString(heap.top()) << endl;
    printHeap(heap);
    cout << endl;

    cout << "heap.pop()" << endl;
    heap.pop();
    cout << "size = " << heap.size() << endl;
    printHeap(heap);

    return 0;
}