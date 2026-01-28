#pragma once

#include <algorithm>
#include <stdexcept>

template <typename T> typename T::iterator easyfind(T &container, int n)
{
    typename T::iterator itr = std::find(container.begin(), container.end(), n);
    if (itr == container.end())
    {
        throw std::logic_error("N not found");
    }
    return itr;
}