// Exercise 04 — Tests (read-only)
//
// This test file and ex04.cpp are separate translation units.
// Both include ex04.h.  If the function were defined (non-inline)
// in the header, linking these two TUs would produce a
// "multiple definition" error.

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-01-ex04: Header/Source Split");

TEST(runner, "multiply_add computes a*b + c") {
    ASSERT_EQ(multiply_add(2, 3, 4), 10);
    ASSERT_EQ(multiply_add(0, 5, 1), 1);
    ASSERT_EQ(multiply_add(-1, 3, 3), 0);
}

TEST(runner, "multiply_add with zero multiplier") {
    ASSERT_EQ(multiply_add(5, 0, 7), 7);
}

TESTKIT_MAIN(runner)
