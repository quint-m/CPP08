#include "MutantStack.hpp"
#include <iostream>
#include <sstream>
#include <string>

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"

static int t_passed = 0; // NOLINT
static int t_total = 0;  // NOLINT

void result(const std::string &msg, bool passed)
{
    t_total++;
    if (passed)
    {
        std::cout << GREEN << "[passed]" << RESET << " " << msg << '\n';
        t_passed++;
        return;
    }
    std::cout << RED << "[failed]" << RESET << " " << msg << '\n';
}

// NOLINTBEGIN
void test_stack_operations()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    result("Top returns last pushed value", mstack.top() == 17);
    mstack.pop();
    result("Pop removes top element", mstack.top() == 5);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    result("Size after pushes", mstack.size() == 5);
}

void test_iterators()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::ostringstream oss;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
    {
        oss << *it << ' ';
    }
    std::string expected = "5 17 3 5 737 0 ";
    result("Iterator traverses all elements in order", oss.str() == expected);

    // Const iterator test
    const MutantStack<int> &cmstack = mstack;
    std::ostringstream oss2;
    for (MutantStack<int>::const_iterator it = cmstack.begin(); it != cmstack.end(); ++it)
    {
        oss2 << *it << ' ';
    }
    result("Const iterator traverses all elements in order", oss2.str() == expected);
}

void test_empty_stack()
{
    MutantStack<int> mstack;
    result("Empty stack size is zero", mstack.size() == 0);
    result("begin() == end() for empty stack", mstack.begin() == mstack.end());
}
// NOLINTEND

int main()
{
    std::cout << "\n--- MutantStack Tests ---\n";
    test_stack_operations();
    test_iterators();
    test_empty_stack();
    std::cout << "\n" << t_passed << "/" << t_total << " tests passed.\n";
    return t_passed == t_total ? 0 : 1;
}