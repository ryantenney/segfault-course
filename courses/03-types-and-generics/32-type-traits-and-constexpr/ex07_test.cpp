// Exercise 07 -- Tests (read-only)
//
// Each test calls ex07_gate() first. While that gate contains TODO(),
// all tests show as "skipped". Once the student removes TODO() from the
// gate AND implements the consteval functions, the tests will run.
//
// The consteval functions are called with compile-time constant arguments
// and their results stored in constexpr variables, proving compile-time
// evaluation.

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("03-32-ex07: consteval (Immediate Functions)");

TEST(runner, "compile_time_square(5) is 25") {
    ex07_gate();
    constexpr int result = compile_time_square(5);
    ASSERT_EQ(result, 25);
}

TEST(runner, "compile_time_square(0) is 0") {
    ex07_gate();
    constexpr int result = compile_time_square(0);
    ASSERT_EQ(result, 0);
}

TEST(runner, "compile_time_square(-3) is 9") {
    ex07_gate();
    constexpr int result = compile_time_square(-3);
    ASSERT_EQ(result, 9);
}

TEST(runner, "compile_time_abs(5) is 5") {
    ex07_gate();
    constexpr int result = compile_time_abs(5);
    ASSERT_EQ(result, 5);
}

TEST(runner, "compile_time_abs(-7) is 7") {
    ex07_gate();
    constexpr int result = compile_time_abs(-7);
    ASSERT_EQ(result, 7);
}

TEST(runner, "compile_time_abs(0) is 0") {
    ex07_gate();
    constexpr int result = compile_time_abs(0);
    ASSERT_EQ(result, 0);
}

TEST(runner, "compile_time_gcd(12, 8) is 4") {
    ex07_gate();
    constexpr int result = compile_time_gcd(12, 8);
    ASSERT_EQ(result, 4);
}

TEST(runner, "compile_time_gcd(17, 13) is 1 (coprime)") {
    ex07_gate();
    constexpr int result = compile_time_gcd(17, 13);
    ASSERT_EQ(result, 1);
}

TEST(runner, "compile_time_gcd(100, 25) is 25") {
    ex07_gate();
    constexpr int result = compile_time_gcd(100, 25);
    ASSERT_EQ(result, 25);
}

TESTKIT_MAIN(runner)
