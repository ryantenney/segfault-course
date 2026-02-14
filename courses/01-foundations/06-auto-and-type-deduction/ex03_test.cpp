// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-06-ex03: auto in range-for");

TEST(runner, "sum returns the total of all elements") {
    ASSERT_EQ(sum({1, 2, 3, 4, 5}), 15);
    ASSERT_EQ(sum({}), 0);
    ASSERT_EQ(sum({-1, 1}), 0);
}

TEST(runner, "negate_all flips the sign of every element") {
    std::vector<int> v = {1, -2, 3, 0};
    negate_all(v);
    ASSERT_EQ(v[0], -1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], -3);
    ASSERT_EQ(v[3], 0);
}

TEST(runner, "join produces a comma-separated string") {
    ASSERT_EQ(join({1, 2, 3}), "1,2,3");
    ASSERT_EQ(join({42}), "42");
    ASSERT_EQ(join({}), std::string(""));
}

TEST(runner, "exclaim_all appends ! to every string") {
    std::vector<std::string> v = {"hello", "world"};
    exclaim_all(v);
    ASSERT_EQ(v[0], "hello!");
    ASSERT_EQ(v[1], "world!");
}

TEST(runner, "contains returns true when target is present") {
    std::vector<std::string> v = {"apple", "banana", "cherry"};
    ASSERT_TRUE(contains(v, "banana"));
    ASSERT_FALSE(contains(v, "grape"));
}

TEST(runner, "contains returns false for empty vector") {
    std::vector<std::string> v;
    ASSERT_FALSE(contains(v, "anything"));
}

TESTKIT_MAIN(runner)
