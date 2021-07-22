#ifndef _SHARED_MY_SERIALIZATION_H_
#define _SHARED_MY_SERIALIZATION_H_

#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& result)
{
    os << "[";

    if (result.size() > 0) {
        os << result[0];
    }

    for (size_t i = 1; i < result.size(); ++i) {
        os << ", " << result[i];
    }

    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& result)
{
    os << "[";

    if (result.size() > 0) {
        os << result[0];
    }

    for (size_t i = 1; i < result.size(); ++i) {
        os << ", " << result[i];
    }

    os << "]";

    return os;
}

#endif // _SHARED_MY_SERIALIZATION_H_