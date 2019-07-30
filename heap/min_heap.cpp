#include <iostream>

#include "min_heap.h"

using namespace std;

int main()
{
    MinHeap<int, string> minHeap;

    minHeap.insert(1400, "Frontend interview 01");
    minHeap.insert(1600, "Frontend interview 02");
    minHeap.insert(1200, "Lunch time");
    minHeap.insert(1500, "Backend interview 01");
    minHeap.insert( 930, "Project 01 daily meeting");
    minHeap.insert( 920, "Project 02 daily meeting");
    minHeap.insert(1530, "Canada daily meeting");
    minHeap.insert(1100, "Tech meeting");

    while(!minHeap.empty()) {
        auto item = minHeap.extract();
        cout<<item.key<<" : "<<item.value<<endl;
    }

    return 0;
}