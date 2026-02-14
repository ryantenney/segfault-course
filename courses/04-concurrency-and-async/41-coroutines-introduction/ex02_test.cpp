// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. range() yields the correct sequence of integers.
//   2. range() works with range-for loops via iterators.
//   3. An empty range yields nothing.

#include <testkit/testkit.h>
#include <vector>
#include "ex02.h"

static testkit::TestRunner runner("04-41-ex02: Range-for with Generator");

TEST(runner, "range yields values using next()") {
    ex02_gate();
    auto gen = range(0, 3);
    std::vector<int> result;
    while (gen.next()) {
        result.push_back(gen.value());
    }
    std::vector<int> expected = {0, 1, 2};
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "range works in range-for loop") {
    ex02_gate();
    std::vector<int> result;
    for (int v : range(1, 5)) {
        result.push_back(v);
    }
    std::vector<int> expected = {1, 2, 3, 4};
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "empty range yields nothing") {
    ex02_gate();
    std::vector<int> result;
    for (int v : range(5, 5)) {
        result.push_back(v);
    }
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "range with negative start") {
    ex02_gate();
    std::vector<int> result;
    for (int v : range(-2, 2)) {
        result.push_back(v);
    }
    std::vector<int> expected = {-2, -1, 0, 1};
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TESTKIT_MAIN(runner)
