// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-06-ex04: Trailing Return Types");

TEST(runner, "add returns the sum") {
    ASSERT_EQ(add(2, 3), 5);
    ASSERT_EQ(add(-1, 1), 0);
    ASSERT_EQ(add(0, 0), 0);
}

TEST(runner, "multiply returns the product") {
    ASSERT_EQ(multiply(2.0, 3.0), 6.0);
    ASSERT_EQ(multiply(-1.5, 2.0), -3.0);
    ASSERT_EQ(multiply(0.0, 99.0), 0.0);
}

TEST(runner, "make_greeting formats correctly") {
    ASSERT_EQ(make_greeting("Alice"), "Hello, Alice!");
    ASSERT_EQ(make_greeting("World"), "Hello, World!");
}

TEST(runner, "clamp constrains value to range") {
    ASSERT_EQ(clamp(5, 0, 10), 5);
    ASSERT_EQ(clamp(-3, 0, 10), 0);
    ASSERT_EQ(clamp(15, 0, 10), 10);
    ASSERT_EQ(clamp(0, 0, 10), 0);
    ASSERT_EQ(clamp(10, 0, 10), 10);
}

TESTKIT_MAIN(runner)
