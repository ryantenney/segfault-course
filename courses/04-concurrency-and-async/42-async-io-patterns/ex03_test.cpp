// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. future_read() returns a valid future.
//   2. The future contains the correct value.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("04-42-ex03: Future-based Wrapper");

TEST(runner, "future_read returns a ready future") {
    auto f = future_read();
    // Since our callback-based API is synchronous, the future is ready
    // immediately.
    auto result = f.get();
    ASSERT_EQ(result, "future data");
}

TEST(runner, "future_read can be called multiple times") {
    auto f1 = future_read();
    auto f2 = future_read();
    ASSERT_EQ(f1.get(), "future data");
    ASSERT_EQ(f2.get(), "future data");
}

TEST(runner, "future holds a string value") {
    auto f = future_read();
    std::string result = f.get();
    ASSERT_FALSE(result.empty());
}

TESTKIT_MAIN(runner)
