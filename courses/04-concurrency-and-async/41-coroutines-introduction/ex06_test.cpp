// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. naturals() yields 0, 1, 2, 3, ... indefinitely.
//   2. take() pulls exactly n values from a generator.

#include <testkit/testkit.h>
#include <vector>
#include "ex06.h"

static testkit::TestRunner runner("04-41-ex06: Infinite Sequence");

TEST(runner, "take 5 from naturals yields 0..4") {
    ex06_gate();
    auto gen = naturals();
    auto result = take(gen, 5);
    std::vector<int> expected = {0, 1, 2, 3, 4};
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "take 0 from naturals yields empty") {
    ex06_gate();
    auto gen = naturals();
    auto result = take(gen, 0);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "take 10 from naturals yields 0..9") {
    ex06_gate();
    auto gen = naturals();
    auto result = take(gen, 10);
    ASSERT_EQ(result.size(), 10u);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(result[static_cast<size_t>(i)], i);
    }
}

TEST(runner, "consecutive takes advance the generator") {
    ex06_gate();
    auto gen = naturals();
    auto first = take(gen, 3);
    auto second = take(gen, 3);
    std::vector<int> expected_first = {0, 1, 2};
    std::vector<int> expected_second = {3, 4, 5};
    ASSERT_EQ(first.size(), expected_first.size());
    ASSERT_EQ(second.size(), expected_second.size());
    for (size_t i = 0; i < expected_first.size(); ++i) {
        ASSERT_EQ(first[i], expected_first[i]);
    }
    for (size_t i = 0; i < expected_second.size(); ++i) {
        ASSERT_EQ(second[i], expected_second[i]);
    }
}

TESTKIT_MAIN(runner)
