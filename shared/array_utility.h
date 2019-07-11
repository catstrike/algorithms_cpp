#ifndef _SHARED_ARRAY_UTILITY_H_
#define _SHARED_ARRAY_UTILITY_H_

#include <iostream> // std::cout, std::endl
#include <vector> // std::vector

template <class TValue>
void print_array(const std::vector<TValue> &array)
{
    for (auto item : array) {
        std::cout<<item<<" ";
    }

    std::cout<<std::endl;
}

#endif // _SHARED_ARRAY_UTILITY_H_