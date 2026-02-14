// Exercise 04 -- Tests (read-only)
//
// Verifies template argument deduction and explicit template arguments.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("03-29-ex04: Template Argument Deduction");

TEST(runner, "clamp_value with int: value in range") {
    ASSERT_EQ(clamp_value(5, 0, 10), 5);
}

TEST(runner, "clamp_value with int: value below range") {
    ASSERT_EQ(clamp_value(-3, 0, 10), 0);
}

TEST(runner, "clamp_value with int: value above range") {
    ASSERT_EQ(clamp_value(15, 0, 10), 10);
}

TEST(runner, "clamp_value with double") {
    double result = clamp_value(3.14, 0.0, 2.0);
    ASSERT_TRUE(result > 1.99 && result < 2.01);
}

TEST(runner, "clamp_value at boundary") {
    ASSERT_EQ(clamp_value(0, 0, 10), 0);
    ASSERT_EQ(clamp_value(10, 0, 10), 10);
}

TEST(runner, "as_unsigned converts negative to unsigned") {
    // -1 as unsigned int is the maximum unsigned int value
    unsigned int result = as_unsigned<unsigned int>(-1);
    ASSERT_TRUE(result > 0u);
}

TEST(runner, "as_unsigned converts positive value") {
    unsigned int result = as_unsigned<unsigned int>(42);
    ASSERT_EQ(result, 42u);
}

TEST(runner, "as_unsigned to unsigned long") {
    unsigned long result = as_unsigned<unsigned long>(100);
    ASSERT_EQ(result, 100ul);
}

TEST(runner, "add_mixed int and double to double") {
    double result = add_mixed<double>(3, 4.5);
    ASSERT_TRUE(result > 7.49 && result < 7.51);
}

TEST(runner, "add_mixed int and int to long") {
    long result = add_mixed<long>(1000000, 2000000);
    ASSERT_EQ(result, 3000000L);
}

TEST(runner, "add_mixed double and int to int truncates") {
    int result = add_mixed<int>(3.7, 4);
    ASSERT_EQ(result, 7);
}

TESTKIT_MAIN(runner)
