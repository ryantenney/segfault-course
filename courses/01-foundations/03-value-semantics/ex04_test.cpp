// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <cmath>

#include "ex04.h"

static testkit::TestRunner runner("01-03-ex04: Const Correctness Chain");

static bool approx_eq(double a, double b, double eps = 0.001) {
    return std::fabs(a - b) < eps;
}

TEST(runner, "celsius returns the stored temperature") {
    Temperature t(25.0);
    ASSERT_TRUE(approx_eq(t.celsius(), 25.0));
}

TEST(runner, "fahrenheit converts correctly") {
    Temperature t(0.0);
    ASSERT_TRUE(approx_eq(t.fahrenheit(), 32.0));
    Temperature t2(100.0);
    ASSERT_TRUE(approx_eq(t2.fahrenheit(), 212.0));
}

TEST(runner, "is_freezing returns true at or below 0") {
    Temperature cold(-5.0);
    ASSERT_TRUE(cold.is_freezing());
    Temperature zero(0.0);
    ASSERT_TRUE(zero.is_freezing());
    Temperature warm(1.0);
    ASSERT_FALSE(warm.is_freezing());
}

TEST(runner, "adjust modifies the temperature") {
    Temperature t(20.0);
    t.adjust(5.0);
    ASSERT_TRUE(approx_eq(t.celsius(), 25.0));
    t.adjust(-30.0);
    ASSERT_TRUE(approx_eq(t.celsius(), -5.0));
}

TEST(runner, "describe_temp works through const reference") {
    const Temperature cold(-10.0);
    ASSERT_EQ(describe_temp(cold), std::string("COLD"));
    const Temperature warm(25.0);
    ASSERT_EQ(describe_temp(warm), std::string("WARM"));
}

TEST(runner, "warmer_celsius returns higher temperature") {
    const Temperature a(10.0);
    const Temperature b(30.0);
    ASSERT_TRUE(approx_eq(warmer_celsius(a, b), 30.0));
    ASSERT_TRUE(approx_eq(warmer_celsius(b, a), 30.0));
}

TESTKIT_MAIN(runner)
