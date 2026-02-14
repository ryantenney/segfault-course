// Exercise 07 -- Tests (read-only)
//
// Verifies default template parameters with custom comparators.

#include <string>
#include <functional>
#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("03-29-ex07: Default Template Parameter");

TEST(runner, "min_of with default comparator (int)") {
    ASSERT_EQ(min_of(3, 7), 3);
    ASSERT_EQ(min_of(10, 2), 2);
}

TEST(runner, "min_of with equal values") {
    ASSERT_EQ(min_of(5, 5), 5);
}

TEST(runner, "min_of with default comparator (string)") {
    std::string a = "banana";
    std::string b = "apple";
    ASSERT_EQ(min_of(a, b), std::string("apple"));
}

TEST(runner, "min_of with std::greater gives maximum") {
    int result = min_of(3, 7, std::greater<int>{});
    ASSERT_EQ(result, 7);
}

TEST(runner, "min_of with custom lambda") {
    // Compare by absolute value
    auto by_abs = [](int a, int b) { return (a < 0 ? -a : a) < (b < 0 ? -b : b); };
    ASSERT_EQ(min_of(-2, 5, by_abs), -2);
    ASSERT_EQ(min_of(10, -3, by_abs), -3);
}

TEST(runner, "sort_pair with default comparator") {
    auto p = sort_pair(7, 3);
    ASSERT_EQ(p.first, 3);
    ASSERT_EQ(p.second, 7);
}

TEST(runner, "sort_pair already sorted") {
    auto p = sort_pair(1, 9);
    ASSERT_EQ(p.first, 1);
    ASSERT_EQ(p.second, 9);
}

TEST(runner, "sort_pair with strings") {
    auto p = sort_pair(std::string("zebra"), std::string("apple"));
    ASSERT_EQ(p.first, std::string("apple"));
    ASSERT_EQ(p.second, std::string("zebra"));
}

TEST(runner, "sort_pair with std::greater reverses order") {
    auto p = sort_pair(3, 7, std::greater<int>{});
    ASSERT_EQ(p.first, 7);
    ASSERT_EQ(p.second, 3);
}

TEST(runner, "sort_pair with equal values") {
    auto p = sort_pair(5, 5);
    ASSERT_EQ(p.first, 5);
    ASSERT_EQ(p.second, 5);
}

TESTKIT_MAIN(runner)
