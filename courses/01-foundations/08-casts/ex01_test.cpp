// Exercise 01 — Tests (read-only)
//
// Verifies that C-style casts have been replaced with correct C++ casts.

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("01-08-ex01: Replace C-Style Casts");

TEST(runner, "double_to_int truncates fractional part") {
    ASSERT_EQ(double_to_int(3.7), 3);
    ASSERT_EQ(double_to_int(-2.9), -2);
    ASSERT_EQ(double_to_int(0.0), 0);
}

TEST(runner, "int_to_double converts without loss") {
    ASSERT_EQ(int_to_double(42), 42.0);
    ASSERT_EQ(int_to_double(-7), -7.0);
    ASSERT_EQ(int_to_double(0), 0.0);
}

TEST(runner, "ptr_to_int and int_to_ptr round-trip") {
    int x = 99;
    std::uintptr_t addr = ptr_to_int(&x);
    ASSERT_NE(addr, 0u);
    const int* recovered = int_to_ptr(addr);
    ASSERT_EQ(recovered, &x);
    ASSERT_EQ(*recovered, 99);
}

TESTKIT_MAIN(runner)
