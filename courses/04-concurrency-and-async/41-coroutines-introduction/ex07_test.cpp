// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. validated_range() yields correctly for valid inputs.
//   2. validated_range() throws for invalid inputs (start > end).

#include <testkit/testkit.h>
#include <vector>
#include <stdexcept>
#include "ex07.h"

static testkit::TestRunner runner("04-41-ex07: Exception in Coroutine");

TEST(runner, "validated_range(0, 3) yields 0, 1, 2") {
    ex07_gate();
    auto gen = validated_range(0, 3);
    std::vector<int> expected = {0, 1, 2};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
    ASSERT_FALSE(gen.next());
}

TEST(runner, "validated_range(5, 5) yields nothing") {
    ex07_gate();
    auto gen = validated_range(5, 5);
    ASSERT_FALSE(gen.next());
}

TEST(runner, "validated_range(5, 2) throws invalid_argument") {
    ex07_gate();
    auto gen = validated_range(5, 2);
    ASSERT_THROWS(gen.next(), std::invalid_argument);
}

TEST(runner, "validated_range(-1, 2) yields -1, 0, 1") {
    ex07_gate();
    auto gen = validated_range(-1, 2);
    std::vector<int> expected = {-1, 0, 1};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
    ASSERT_FALSE(gen.next());
}

TESTKIT_MAIN(runner)
