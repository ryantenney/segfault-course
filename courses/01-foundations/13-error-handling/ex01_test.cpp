// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-13-ex01: Throw and Catch");

TEST(runner, "divide returns correct result") {
    ASSERT_EQ(divide(10, 2), 5);
    ASSERT_EQ(divide(7, 3), 2);
    ASSERT_EQ(divide(0, 5), 0);
    ASSERT_EQ(divide(-6, 3), -2);
}

TEST(runner, "divide throws on division by zero") {
    ASSERT_THROWS(divide(10, 0), std::runtime_error);
    ASSERT_THROWS(divide(0, 0), std::runtime_error);
}

TEST(runner, "divide throws with correct message") {
    try {
        divide(1, 0);
        ASSERT_TRUE(false);  // should not reach here
    } catch (const std::runtime_error& e) {
        ASSERT_EQ(std::string(e.what()), std::string("division by zero"));
    }
}

TEST(runner, "safe_divide returns result on success") {
    ASSERT_EQ(safe_divide(10, 2), 5);
    ASSERT_EQ(safe_divide(9, 3), 3);
}

TEST(runner, "safe_divide returns -1 on division by zero") {
    ASSERT_EQ(safe_divide(10, 0), -1);
    ASSERT_EQ(safe_divide(0, 0), -1);
}

TESTKIT_MAIN(runner)
