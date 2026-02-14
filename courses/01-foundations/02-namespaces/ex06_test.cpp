// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include <cmath>

#include "ex06.h"

static testkit::TestRunner runner("01-02-ex06: Namespace Alias");

static bool approx_eq(double a, double b, double eps = 0.001) {
    return std::fabs(a - b) < eps;
}

TEST(runner, "convert_km_to_miles delegates correctly") {
    ASSERT_TRUE(approx_eq(converter::convert_km_to_miles(1.0), 0.621371));
    ASSERT_TRUE(approx_eq(converter::convert_km_to_miles(100.0), 62.1371));
    ASSERT_TRUE(approx_eq(converter::convert_km_to_miles(0.0), 0.0));
}

TEST(runner, "convert_miles_to_km delegates correctly") {
    ASSERT_TRUE(approx_eq(converter::convert_miles_to_km(1.0), 1.60934));
    ASSERT_TRUE(approx_eq(converter::convert_miles_to_km(0.0), 0.0));
}

TEST(runner, "convert_kg_to_pounds delegates correctly") {
    ASSERT_TRUE(approx_eq(converter::convert_kg_to_pounds(1.0), 2.20462));
    ASSERT_TRUE(approx_eq(converter::convert_kg_to_pounds(0.0), 0.0));
    ASSERT_TRUE(approx_eq(converter::convert_kg_to_pounds(100.0), 220.462));
}

TESTKIT_MAIN(runner)
