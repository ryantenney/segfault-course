// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. lazy_squares(n) yields the correct sequence of squares.
//   2. Values are produced lazily (only on next() calls).
//   3. lazy_squares(0) yields nothing.

#include <testkit/testkit.h>
#include <vector>
#include "ex05.h"

static testkit::TestRunner runner("04-41-ex05: Lazy Evaluation");

TEST(runner, "lazy_squares(4) yields 0, 1, 4, 9") {
    ex05_gate();
    auto gen = lazy_squares(4);
    std::vector<int> expected = {0, 1, 4, 9};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
    ASSERT_FALSE(gen.next());
}

TEST(runner, "lazy_squares(1) yields only 0") {
    ex05_gate();
    auto gen = lazy_squares(1);
    ASSERT_TRUE(gen.next());
    ASSERT_EQ(gen.value(), 0);
    ASSERT_FALSE(gen.next());
}

TEST(runner, "lazy_squares(0) yields nothing") {
    ex05_gate();
    auto gen = lazy_squares(0);
    ASSERT_FALSE(gen.next());
}

TEST(runner, "lazy_squares(6) yields 0, 1, 4, 9, 16, 25") {
    ex05_gate();
    auto gen = lazy_squares(6);
    std::vector<int> expected = {0, 1, 4, 9, 16, 25};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
    ASSERT_FALSE(gen.next());
}

TESTKIT_MAIN(runner)
