// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-16-ex02: Const Iteration");

TEST(runner, "contains finds an existing element") {
    std::vector<int> vec = {10, 20, 30, 40};
    ASSERT_TRUE(contains(vec, 30));
}

TEST(runner, "contains returns false for missing element") {
    std::vector<int> vec = {10, 20, 30, 40};
    ASSERT_FALSE(contains(vec, 99));
}

TEST(runner, "contains returns false for empty vector") {
    std::vector<int> vec;
    ASSERT_FALSE(contains(vec, 1));
}

TEST(runner, "build_comma_string joins elements") {
    std::vector<std::string> vec = {"alpha", "beta", "gamma"};
    ASSERT_EQ(build_comma_string(vec), std::string("alpha, beta, gamma"));
}

TEST(runner, "build_comma_string with single element") {
    std::vector<std::string> vec = {"only"};
    ASSERT_EQ(build_comma_string(vec), std::string("only"));
}

TEST(runner, "build_comma_string with empty vector") {
    std::vector<std::string> vec;
    ASSERT_EQ(build_comma_string(vec), std::string(""));
}

TEST(runner, "first_positive finds positive element") {
    std::vector<int> vec = {-3, -1, 0, 5, 2};
    auto it = first_positive(vec);
    ASSERT_TRUE(it != vec.cend());
    ASSERT_EQ(*it, 5);
}

TEST(runner, "first_positive returns cend when none exist") {
    std::vector<int> vec = {-5, -2, 0, -1};
    auto it = first_positive(vec);
    ASSERT_TRUE(it == vec.cend());
}

TESTKIT_MAIN(runner)
