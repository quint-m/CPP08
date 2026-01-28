#include "Span.hpp"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

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

bool add_wrapper(Span &span, int n)
{
    try
    {
        span.addNumber(n);
        return true;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

bool add_multiple_wrapper(Span &span, std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end)
{
    try
    {
        span.addMultiple(begin, end);
        return true;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

// NOLINTBEGIN
void test_add_multiple()
{
    {
        // Fill with empty range
        Span s(3);
        std::vector<int> v;
        bool success = add_multiple_wrapper(s, v.begin(), v.end());
        result("addMultiple with empty range does not throw", success);
    }

    {
        // Fill exactly to capacity
        Span s(4);
        std::vector<int> v = {1, 2, 3, 4};
        bool success = add_multiple_wrapper(s, v.begin(), v.end());
        result("addMultiple fills to capacity", success && s.shortestSpan() == 1 && s.longestSpan() == 3);
    }

    {
        // Fill partially, then add more
        Span s(5);
        std::vector<int> v1 = {10, 20};
        std::vector<int> v2 = {30, 40, 50};
        bool success = add_multiple_wrapper(s, v1.begin(), v1.end());
        if (success)
            success = add_multiple_wrapper(s, v2.begin(), v2.end());
        result("addMultiple in parts fills span", success && s.shortestSpan() == 10 && s.longestSpan() == 40);
    }

    {
        // Use different iterator types (const_iterator)
        Span s(3);
        const std::vector<int> v = {7, 8, 9};
        bool success = add_multiple_wrapper(s, v.cbegin(), v.cend());
        result("addMultiple works with const_iterator", success && s.shortestSpan() == 1 && s.longestSpan() == 2);
    }

    // Test addMultiple and exception when range too large
    {
        Span s(5);
        std::vector<int> v = {1, 2, 3, 4, 5};
        s.addMultiple(v.begin(), v.end());
        result("addMultiple fills span", s.shortestSpan() == 1 && s.longestSpan() == 4);
        std::vector<int> v2 = {6, 7};
        bool success = add_multiple_wrapper(s, v2.begin(), v2.end());
        result("addMultiple throws when overfilling", success == false); // We expect failure here
    }
}

void test_orthodox_form()
{
    // Test Orthodox Canonical Form
    {
        Span s1(5);
        s1.addNumber(1);
        s1.addNumber(2);
        Span s2 = s1; // Copy constructor
        Span s3(10);
        s3 = s1; // Assignment operator
        result("Copy constructor copies elements", s2.shortestSpan() == 1 && s2.longestSpan() == 1);
        result("Assignment operator copies elements", s3.shortestSpan() == 1 && s3.longestSpan() == 1);
        s1.addNumber(3);
        result("Copy is independent of original", s2.longestSpan() == 1);
    }
}

void test_add_number()
{
    // Test addNumber and exception when full
    {
        Span s(2);
        bool success = add_wrapper(s, 10);
        success = success && add_wrapper(s, 20);
        success = success && add_wrapper(s, 30); // This should fail
        result("addNumber throws when full", success == false);
    }
}

void test_shortest_longest_span()
{
    // Test shortestSpan and longestSpan with too few elements
    {
        Span s(2);
        s.addNumber(1);
        bool shortest_thrown = false;
        bool longest_thrown = false;
        try
        {
            s.shortestSpan();
        }
        catch (const std::out_of_range &)
        {
            shortest_thrown = true;
        }
        try
        {
            s.longestSpan();
        }
        catch (const std::out_of_range &)
        {
            longest_thrown = true;
        }
        result("shortestSpan throws with <2 elements", shortest_thrown);
        result("longestSpan throws with <2 elements", longest_thrown);
    }

    // Test shortestSpan and longestSpan with normal input
    {
        Span s(5);
        s.addNumber(6);
        s.addNumber(3);
        s.addNumber(17);
        s.addNumber(9);
        s.addNumber(11);
        result("shortestSpan computes correctly", s.shortestSpan() == 2);
        result("longestSpan computes correctly", s.longestSpan() == 14);
    }
}

void test_10000_numbers()
{
    // Test with 10,000 numbers
    {
        const int N = 10000;
        Span s(N);
        std::vector<int> v;
        for (int i = 0; i < N; ++i)
            v.push_back(i * 2);
        s.addMultiple(v.begin(), v.end());
        result("10,000 numbers: shortestSpan == 2", s.shortestSpan() == 2);
        result("10,000 numbers: longestSpan == 19998", s.longestSpan() == (N - 1) * 2);
    }
}

void test_negative_numbers_and_duplicates()
{
    // Test negative numbers and duplicates
    {
        Span s(6);
        s.addNumber(-10);
        s.addNumber(-20);
        s.addNumber(0);
        s.addNumber(10);
        s.addNumber(-10);
        s.addNumber(20);
        result("Handles negative numbers", s.shortestSpan() == 0 && s.longestSpan() == 40);
    }
}
// NOLINTEND

int main()
{
    test_add_multiple();
    test_orthodox_form();
    test_add_number();
    test_shortest_longest_span();
    test_10000_numbers();
    test_negative_numbers_and_duplicates();
    std::cout << (t_passed == t_total ? GREEN : RED) << "[Summary] Passed " << t_passed << "/" << t_total << RESET
              << '\n';
    return t_passed == t_total ? 0 : 1;
}