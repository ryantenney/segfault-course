// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. async_read calls the callback exactly once.
//   2. The callback receives "hello, world".

#include <testkit/testkit.h>
#include <string>
#include "ex01.h"

static testkit::TestRunner runner("04-42-ex01: Callback-based API");

TEST(runner, "async_read calls callback with hello world") {
    std::string result;
    async_read([&result](const std::string& data) {
        result = data;
    });
    ASSERT_EQ(result, "hello, world");
}

TEST(runner, "async_read calls callback exactly once") {
    int call_count = 0;
    async_read([&call_count](const std::string&) {
        ++call_count;
    });
    ASSERT_EQ(call_count, 1);
}

TEST(runner, "callback receives non-empty string") {
    bool received = false;
    async_read([&received](const std::string& data) {
        received = !data.empty();
    });
    ASSERT_TRUE(received);
}

TESTKIT_MAIN(runner)
