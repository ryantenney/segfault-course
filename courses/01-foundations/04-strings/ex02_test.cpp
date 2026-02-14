// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-04-ex02: Fix String Copies");

TEST(runner, "starts_with detects matching prefix") {
    ASSERT_TRUE(starts_with("hello world", "hello"));
    ASSERT_TRUE(starts_with("hello", "hello"));
    ASSERT_TRUE(starts_with("hello", ""));
    ASSERT_FALSE(starts_with("hello", "world"));
    ASSERT_FALSE(starts_with("hi", "hello"));
}

TEST(runner, "ends_with detects matching suffix") {
    ASSERT_TRUE(ends_with("hello world", "world"));
    ASSERT_TRUE(ends_with("hello", "hello"));
    ASSERT_TRUE(ends_with("hello", ""));
    ASSERT_FALSE(ends_with("hello", "world"));
    ASSERT_FALSE(ends_with("hi", "hello"));
}

TEST(runner, "contains detects a substring") {
    ASSERT_TRUE(contains("hello world", "lo wo"));
    ASSERT_TRUE(contains("hello", "hello"));
    ASSERT_TRUE(contains("hello", ""));
    ASSERT_FALSE(contains("hello", "xyz"));
    ASSERT_FALSE(contains("hi", "hello"));
}

// These tests pass string literals directly — no std::string involved.
// If your parameters are still const std::string&, each literal creates
// a temporary std::string on the heap. With string_view, zero allocations.
TEST(runner, "works with string literals without allocation") {
    ASSERT_TRUE(starts_with("config.yaml", "config"));
    ASSERT_TRUE(ends_with("photo.jpg", ".jpg"));
    ASSERT_TRUE(contains("user@example.com", "@"));
}

TESTKIT_MAIN(runner)
