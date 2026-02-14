// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. ReadAwaitable captures the callback result.
//   2. coroutine_read() co_awaits and returns the data.

#include <testkit/testkit.h>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("04-42-ex04: Callback to Coroutine");

TEST(runner, "coroutine_read returns awaited data") {
    ex04_gate();
    auto task = coroutine_read();
    ASSERT_TRUE(task.done());
    ASSERT_EQ(task.result(), "awaited data");
}

TEST(runner, "coroutine_read can be called multiple times") {
    ex04_gate();
    auto t1 = coroutine_read();
    auto t2 = coroutine_read();
    ASSERT_EQ(t1.result(), "awaited data");
    ASSERT_EQ(t2.result(), "awaited data");
}

TEST(runner, "ReadAwaitable captures the data") {
    ex04_gate();
    ReadAwaitable awaitable;
    // After await_ready, data should be populated
    awaitable.await_ready();
    std::string result = awaitable.await_resume();
    ASSERT_EQ(result, "awaited data");
}

TESTKIT_MAIN(runner)
