// Exercise 08 — Tests (read-only)
//
// This test file, ex08_math.cpp, and ex08_format.cpp are three
// separate translation units linked into one executable.
//
// The include graph:
//   ex08_test.cpp    → ex08_format.h → ex08_math.h
//   ex08_format.cpp  → ex08_format.h → ex08_math.h
//   ex08_math.cpp    → ex08_math.h
//
// Thanks to #pragma once, ex08_math.h is included at most once per TU
// even though multiple headers reference it.

#include <testkit/testkit.h>

#include "ex08_format.h"

static testkit::TestRunner runner("01-01-ex08: Multi-TU Build");

// -- Math tests --

TEST(runner, "abs_val returns absolute value") {
    ASSERT_EQ(abs_val(5), 5);
    ASSERT_EQ(abs_val(-3), 3);
    ASSERT_EQ(abs_val(0), 0);
}

TEST(runner, "max_val returns the larger value") {
    ASSERT_EQ(max_val(3, 7), 7);
    ASSERT_EQ(max_val(7, 3), 7);
    ASSERT_EQ(max_val(4, 4), 4);
}

TEST(runner, "clamp_val restricts to [lo, hi]") {
    ASSERT_EQ(clamp_val(5, 0, 10), 5);
    ASSERT_EQ(clamp_val(-1, 0, 10), 0);
    ASSERT_EQ(clamp_val(15, 0, 10), 10);
}

// -- Format tests --

TEST(runner, "format_signed with positive value") {
    ASSERT_EQ(format_signed(5), std::string("+5"));
}

TEST(runner, "format_signed with negative value") {
    ASSERT_EQ(format_signed(-3), std::string("-3"));
}

TEST(runner, "format_signed with zero") {
    ASSERT_EQ(format_signed(0), std::string("+0"));
}

TEST(runner, "format_range clamps and orders") {
    ASSERT_EQ(format_range(3, 8, 0, 10), std::string("3..8"));
    ASSERT_EQ(format_range(10, 3, 0, 8), std::string("3..8"));
    ASSERT_EQ(format_range(-5, 20, 0, 10), std::string("0..10"));
}

TESTKIT_MAIN(runner)
