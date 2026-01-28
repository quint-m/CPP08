#include "easyfind.hpp"
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"

static int t_passed = 0; // NOLINT
static int t_total = 0;  // NOLINT

std::string capture(const std::function<void()> &func)
{
    std::streambuf *orig = std::cout.rdbuf();
    std::ostringstream capture;

    std::cout.rdbuf(capture.rdbuf());
    func();
    std::cout.rdbuf(orig);

    return capture.str();
}

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
void test_int_container()
{
    std::vector<int> ints = {1, 2, 3, 4, 5, 6}; // NOLINT(readability-magic-numbers)

    try
    {
        auto found = easyfind(ints, 1);
        result("Finds an integer in vector (int)", *found == 1);
    }
    catch (const std::exception &e)
    {
        result("Finds an integer in vector (int)", false);
    }

    try
    {
        easyfind(ints, -1);
        result("Finds an integer in vector (int)", false);
    }
    catch (const std::exception &e)
    {
        result("Can't find a vector that doesn't exist", true);
    }
}

void test_char_container()
{
    std::vector<char> chars = {'a', 'b', 'c', 'd'}; // NOLINT(readability-magic-numbers)

    try
    {
        auto found = easyfind(chars, 'a');
        result("Finds an integer in vector (char)", *found == 'a');
    }
    catch (const std::exception &e)
    {
        result("Finds an integer in vector (char)", false);
    }

    try
    {
        easyfind(chars, 65); // see if it doesn't falsely cast int -> char
        result("Finds an integer in vector (char)", false);
    }
    catch (const std::exception &e)
    {
        result("Can't find a vector that doesn't exist", true);
    }
}

void test_int_deque()
{
    std::deque<int> dq = {1, 222, -20};

    try
    {
        easyfind(dq, 222);
        result("Finds a float in deque (int)", true);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        result("Finds a float in deque (int)", false);
    }

    try
    {
        easyfind(dq, -10000);
        result("Doesn't find a int in deque that doesn't exist", false);
    }
    catch (const std::exception &e)
    {
        result("Doesn't find a int in deque that doesn't exist", true);
    }
}
// NOLINTEND

int main()
{
    test_int_container();
    test_int_deque();
    test_char_container();
    return 0;
}