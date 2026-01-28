#pragma once

#include <stack>

template <typename T> class MutantStack : public std::stack<T> // NOLINT(cppcoreguidelines-special-member-functions)
{
  public:
    MutantStack();

    ~MutantStack();

    MutantStack(const MutantStack &other);

    MutantStack &operator=(const MutantStack &other);

    typedef typename std::stack<T>::container_type::iterator iterator;             // NOLINT(modernize-use-using)
    typedef typename std::stack<T>::container_type::const_iterator const_iterator; // NOLINT(modernize-use-using)

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;
};

#include "MutantStack.tpp"