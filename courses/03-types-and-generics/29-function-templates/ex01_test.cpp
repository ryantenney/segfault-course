// Exercise 01 -- Tests (read-only)
//
// Verifies the generic max_of function template with multiple types.

#include <string>
#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("03-29-ex01: Generic Max Function");

TEST(runner, "max_of with ints") {
    ASSERT_EQ(max_of(3, 7), 7);
    ASSERT_EQ(max_of(10, 2), 10);
}

TEST(runner, "max_of with equal ints returns b") {
    ASSERT_EQ(max_of(5, 5), 5);
}

TEST(runner, "max_of with negative ints") {
    ASSERT_EQ(max_of(-3, -7), -3);
    ASSERT_EQ(max_of(-1, 0), 0);
}

TEST(runner, "max_of with doubles") {
    double result = max_of(3.14, 2.71);
    ASSERT_TRUE(result > 3.13 && result < 3.15);
}

TEST(runner, "max_of with strings uses lexicographic order") {
    std::string a = "apple";
    std::string b = "banana";
    ASSERT_EQ(max_of(a, b), std::string("banana"));
}

TEST(runner, "max_of with chars") {
    ASSERT_EQ(max_of('a', 'z'), 'z');
    ASSERT_EQ(max_of('Z', 'A'), 'Z');
}

TESTKIT_MAIN(runner)
