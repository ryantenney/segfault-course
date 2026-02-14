// Exercise 02 — Tests (read-only)
//
// These tests call the functions using fully-qualified names.
// They work with either the verbose or compact namespace syntax.

#include <testkit/testkit.h>
#include <cmath>

#include "ex02.h"

static testkit::TestRunner runner("01-02-ex02: Nested Namespaces");

// Helper: compare floating point with tolerance
static bool approx_eq(double a, double b, double eps = 0.001) {
    return std::fabs(a - b) < eps;
}

TEST(runner, "meters_to_feet converts correctly") {
    ASSERT_TRUE(approx_eq(engine::physics::units::meters_to_feet(1.0), 3.28084));
    ASSERT_TRUE(approx_eq(engine::physics::units::meters_to_feet(0.0), 0.0));
    ASSERT_TRUE(approx_eq(engine::physics::units::meters_to_feet(10.0), 32.8084));
}

TEST(runner, "feet_to_meters converts correctly") {
    ASSERT_TRUE(approx_eq(engine::physics::units::feet_to_meters(3.28084), 1.0));
    ASSERT_TRUE(approx_eq(engine::physics::units::feet_to_meters(0.0), 0.0));
}

TEST(runner, "celsius_to_fahrenheit converts correctly") {
    ASSERT_TRUE(approx_eq(engine::physics::units::celsius_to_fahrenheit(0.0), 32.0));
    ASSERT_TRUE(approx_eq(engine::physics::units::celsius_to_fahrenheit(100.0), 212.0));
    ASSERT_TRUE(approx_eq(engine::physics::units::celsius_to_fahrenheit(-40.0), -40.0));
}

TESTKIT_MAIN(runner)
