// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. make_shared_result returns the correct value.
//   2. The shared_future can be .get()-ed multiple times.
//   3. The shared_future can be copied.

#include <testkit/testkit.h>
#include <future>
#include "ex07.h"

static testkit::TestRunner runner("04-39-ex07: Shared Future");

TEST(runner, "make_shared_result(5) returns 50") {
    auto sf = make_shared_result(5);
    ASSERT_EQ(sf.get(), 50);
}

TEST(runner, "shared_future can be get()-ed multiple times") {
    auto sf = make_shared_result(3);
    ASSERT_EQ(sf.get(), 30);
    ASSERT_EQ(sf.get(), 30);
    ASSERT_EQ(sf.get(), 30);
}

TEST(runner, "shared_future can be copied") {
    auto sf1 = make_shared_result(7);
    auto sf2 = sf1;  // copy
    ASSERT_EQ(sf1.get(), 70);
    ASSERT_EQ(sf2.get(), 70);
}

TEST(runner, "make_shared_result(0) returns 0") {
    auto sf = make_shared_result(0);
    ASSERT_EQ(sf.get(), 0);
}

TESTKIT_MAIN(runner)
