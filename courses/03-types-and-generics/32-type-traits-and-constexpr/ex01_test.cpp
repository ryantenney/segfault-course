// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("03-32-ex01: static_assert with Type Traits");

TEST(runner, "numeric_add works with int") {
    ASSERT_EQ(numeric_add(3, 4), 7);
}

TEST(runner, "numeric_add works with double") {
    ASSERT_EQ(numeric_add(1.5, 2.5), 4.0);
}

TEST(runner, "safe_cast converts int to long") {
    ASSERT_EQ(safe_cast<long>(42), 42L);
}

TEST(runner, "safe_cast converts short to int") {
    short s = 10;
    ASSERT_EQ(safe_cast<int>(s), 10);
}

TEST(runner, "require_same returns value when types match") {
    ASSERT_EQ(require_same<int>(42), 42);
}

TEST(runner, "require_same works with string") {
    std::string s = "hello";
    ASSERT_EQ(require_same<std::string>(s), std::string("hello"));
}

TESTKIT_MAIN(runner)
