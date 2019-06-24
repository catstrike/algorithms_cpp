#ifndef _SHARED_H_
#define _SHARED_H_

#include <iostream>
#include <vector>

template <class TValue>
void print_array(const std::vector<TValue> &array)
{
    for (auto item : array) {
        std::cout<<item<<" ";
    }

    std::cout<<std::endl;
}

#endif // _SHARED_H_