#pragma once

#include <vector>

class Span
{
  public:
    Span();
    Span(unsigned int n);

    Span(const Span &other);

    Span &operator=(const Span &other);

    ~Span();

    void addNumber(int n);

    void addMultiple(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end);

    int shortestSpan();

    int longestSpan();

  private:
    unsigned int _size;
    std::vector<int> _elements;
};