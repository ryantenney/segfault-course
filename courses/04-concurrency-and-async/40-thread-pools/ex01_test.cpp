// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. BasicPool creates the requested number of threads.
//   2. The pool can be constructed and destroyed cleanly.

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("04-40-ex01: Fixed Thread Vector");

TEST(runner, "pool with 4 threads has size 4") {
    BasicPool pool(4);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(4));
}

TEST(runner, "pool with 1 thread has size 1") {
    BasicPool pool(1);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(1));
}

TEST(runner, "pool with 8 threads has size 8") {
    BasicPool pool(8);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(8));
}

TEST(runner, "pool destructor completes cleanly") {
    {
        BasicPool pool(4);
        ASSERT_EQ(pool.size(), static_cast<std::size_t>(4));
    }
    // If we get here, the destructor didn't deadlock.
    ASSERT_TRUE(true);
}

TESTKIT_MAIN(runner)
