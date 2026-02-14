// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("02-19-ex06: Lambda Returning Lambda");

TEST(runner, "make_multiplier multiplies by factor") {
    auto triple = make_multiplier(3);
    ASSERT_EQ(triple(4), 12);
    ASSERT_EQ(triple(0), 0);
    ASSERT_EQ(triple(-2), -6);
}

TEST(runner, "make_multiplier with factor 1 is identity") {
    auto identity = make_multiplier(1);
    ASSERT_EQ(identity(42), 42);
}

TEST(runner, "make_multiplier instances are independent") {
    auto double_it = make_multiplier(2);
    auto triple_it = make_multiplier(3);
    ASSERT_EQ(double_it(5), 10);
    ASSERT_EQ(triple_it(5), 15);
}

TEST(runner, "make_adder adds offset") {
    auto add5 = make_adder(5);
    ASSERT_EQ(add5(3), 8);
    ASSERT_EQ(add5(-5), 0);
    ASSERT_EQ(add5(0), 5);
}

TEST(runner, "make_adder with negative offset") {
    auto sub3 = make_adder(-3);
    ASSERT_EQ(sub3(10), 7);
}

TEST(runner, "make_range_checker returns true for values in range") {
    auto in_range = make_range_checker(1, 10);
    ASSERT_TRUE(in_range(1));
    ASSERT_TRUE(in_range(5));
    ASSERT_TRUE(in_range(10));
}

TEST(runner, "make_range_checker returns false for values outside range") {
    auto in_range = make_range_checker(1, 10);
    ASSERT_FALSE(in_range(0));
    ASSERT_FALSE(in_range(11));
    ASSERT_FALSE(in_range(-5));
}

TEST(runner, "make_range_checker works with single-value range") {
    auto exactly_5 = make_range_checker(5, 5);
    ASSERT_TRUE(exactly_5(5));
    ASSERT_FALSE(exactly_5(4));
    ASSERT_FALSE(exactly_5(6));
}

TESTKIT_MAIN(runner)
