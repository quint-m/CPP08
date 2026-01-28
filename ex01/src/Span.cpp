#include "Span.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

Span::Span() : Span(0)
{
}

Span::Span(unsigned int n) : _size(n)
{
    _elements.reserve(_size);
}

Span::Span(const Span &other) : _size(other._size), _elements(other._elements)
{
}

Span &Span::operator=(const Span &other)
{
    if (this == &other)
    {
        return *this;
    }
    _size = other._size;
    _elements = other._elements;
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int n)
{
    if (_elements.size() >= _size)
    {
        throw std::out_of_range("Span is full");
    }
    _elements.push_back(n);
}

/**
 * Shortest span will be found by:
 *  1. Sorting the array to ensure shortest span will be two adjacent elements
 *  2. Compute the difference between the current two adjecent elements
 *  3. Storing the min
 *
 * @return shortest span
 */
int Span::shortestSpan()
{
    if (_elements.size() < 2)
    {
        throw std::out_of_range("Not enough elements in span");
    }

    std::vector<int> copy = _elements;
    std::sort(copy.begin(), copy.end());
    int dist = std::numeric_limits<int>::max();
    for (unsigned int i = 1; i < copy.size(); i++)
    {
        int diff = copy[i] - copy[i - 1];
        dist = std::min(diff, dist);
    }
    return dist;
}

/**
 * Longest span will be found by substracting the smallest from the largest element
 *
 * @return longest span
 */
int Span::longestSpan()
{
    if (_elements.size() < 2)
    {
        throw std::out_of_range("Not enough elements in span");
    }

    auto max = std::max_element(_elements.begin(), _elements.end());
    auto min = std::min_element(_elements.begin(), _elements.end());

    return *max - *min;
}

void Span::addMultiple(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end)
{
    unsigned int distance = std::distance(begin, end);
    if (_elements.size() + distance > _size)
    {
        throw std::out_of_range("Iterator distance exceeds Span size");
    }
    _elements.insert(_elements.end(), begin, end);
}