// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. The header defines the EX01_H include-guard macro.
//   2. The header can safely be included twice.
//   3. The functions produce correct results.

#include <testkit/testkit.h>

#include "ex01.h"

// This second #include is guarded by #ifdef so the file compiles even
// before you add include guards.  Once you define EX01_H as your guard
// macro, this #include activates — and your guards make it a safe no-op.
#ifdef EX01_H
#include "ex01.h"
#endif

static testkit::TestRunner runner("01-01-ex01: Include Guards");

TEST(runner, "header defines the EX01_H guard macro") {
#ifdef EX01_H
    ASSERT_TRUE(true);
#else
    TODO();  // Add include guards to ex01.h
#endif
}

TEST(runner, "add returns the sum of two integers") {
    ASSERT_EQ(add(2, 3), 5);
    ASSERT_EQ(add(-1, 1), 0);
    ASSERT_EQ(add(0, 0), 0);
}

TEST(runner, "distance_squared computes (dx*dx + dy*dy)") {
    ASSERT_EQ(distance_squared({0, 0}, {3, 4}), 25);
    ASSERT_EQ(distance_squared({1, 1}, {1, 1}), 0);
    ASSERT_EQ(distance_squared({-1, -1}, {2, 3}), 25);
}

TESTKIT_MAIN(runner)
