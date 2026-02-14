// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. fibonacci() yields the correct Fibonacci sequence.
//   2. The generator produces values lazily on demand.

#include <testkit/testkit.h>
#include <vector>
#include "ex01.h"

static testkit::TestRunner runner("04-41-ex01: Generator Basics");

TEST(runner, "fibonacci yields first value 0") {
    ex01_gate();  // gate: throws TODO() if not implemented
    auto gen = fibonacci();
    ASSERT_TRUE(gen.next());
    ASSERT_EQ(gen.value(), 0);
}

TEST(runner, "fibonacci yields 0, 1, 1, 2, 3") {
    ex01_gate();
    auto gen = fibonacci();
    std::vector<int> expected = {0, 1, 1, 2, 3};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
}

TEST(runner, "fibonacci yields first 10 values") {
    ex01_gate();
    auto gen = fibonacci();
    std::vector<int> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    for (int e : expected) {
        ASSERT_TRUE(gen.next());
        ASSERT_EQ(gen.value(), e);
    }
}

TEST(runner, "two independent generators produce same sequence") {
    ex01_gate();
    auto gen1 = fibonacci();
    auto gen2 = fibonacci();
    for (int i = 0; i < 5; ++i) {
        ASSERT_TRUE(gen1.next());
        ASSERT_TRUE(gen2.next());
        ASSERT_EQ(gen1.value(), gen2.value());
    }
}

TESTKIT_MAIN(runner)
