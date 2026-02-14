// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-07-ex01: Decompose a pair");

TEST(runner, "try_insert returns true for new key") {
    std::map<std::string, int> m;
    ASSERT_TRUE(try_insert(m, "alpha", 1));
    ASSERT_EQ(m.size(), 1u);
}

TEST(runner, "try_insert returns false for existing key") {
    std::map<std::string, int> m = {{"alpha", 1}};
    ASSERT_FALSE(try_insert(m, "alpha", 2));
    ASSERT_EQ(m["alpha"], 1);  // original value unchanged
}

TEST(runner, "insert_or_get returns new value on insert") {
    std::map<std::string, int> m;
    ASSERT_EQ(insert_or_get(m, "x", 42), 42);
}

TEST(runner, "insert_or_get returns existing value on duplicate") {
    std::map<std::string, int> m = {{"x", 10}};
    ASSERT_EQ(insert_or_get(m, "x", 99), 10);
}

TEST(runner, "min_max returns ordered pair") {
    auto [lo, hi] = min_max(5, 3);
    ASSERT_EQ(lo, 3);
    ASSERT_EQ(hi, 5);
}

TEST(runner, "min_max handles equal values") {
    auto [lo, hi] = min_max(7, 7);
    ASSERT_EQ(lo, 7);
    ASSERT_EQ(hi, 7);
}

TESTKIT_MAIN(runner)
