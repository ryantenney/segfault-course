// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-16-ex01: Manual Iteration");

TEST(runner, "sum_list returns 0 for an empty list") {
    std::list<int> lst;
    ASSERT_EQ(sum_list(lst), 0);
}

TEST(runner, "sum_list adds all elements") {
    std::list<int> lst = {1, 2, 3, 4, 5};
    ASSERT_EQ(sum_list(lst), 15);
}

TEST(runner, "sum_list handles negative numbers") {
    std::list<int> lst = {-3, 7, -2, 8};
    ASSERT_EQ(sum_list(lst), 10);
}

TEST(runner, "double_elements multiplies each element by 2") {
    std::list<int> lst = {1, 2, 3};
    double_elements(lst);
    auto it = lst.begin();
    ASSERT_EQ(*it, 2); ++it;
    ASSERT_EQ(*it, 4); ++it;
    ASSERT_EQ(*it, 6);
}

TEST(runner, "double_elements on empty list does nothing") {
    std::list<int> lst;
    double_elements(lst);
    ASSERT_TRUE(lst.empty());
}

TEST(runner, "find_in_list returns iterator to found element") {
    std::list<std::string> lst = {"alpha", "beta", "gamma"};
    auto it = find_in_list(lst, "beta");
    ASSERT_TRUE(it != lst.end());
    ASSERT_EQ(*it, std::string("beta"));
}

TEST(runner, "find_in_list returns end for missing element") {
    std::list<std::string> lst = {"alpha", "beta", "gamma"};
    auto it = find_in_list(lst, "delta");
    ASSERT_TRUE(it == lst.end());
}

TEST(runner, "find_in_list finds the first occurrence") {
    std::list<std::string> lst = {"x", "y", "x", "z"};
    auto it = find_in_list(lst, "x");
    ASSERT_TRUE(it == lst.begin());
}

TESTKIT_MAIN(runner)
