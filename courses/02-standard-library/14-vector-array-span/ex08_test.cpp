// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex08.h"

#include <cmath>
#include <vector>
#include <array>

static testkit::TestRunner runner("02-14-ex08: Span from Different Sources");

TEST(runner, "compute_average of empty span returns 0.0") {
    std::vector<double> empty;
    ASSERT_TRUE(compute_average(empty) == 0.0);
}

TEST(runner, "compute_average computes the mean") {
    std::vector<double> v = {2.0, 4.0, 6.0};
    ASSERT_TRUE(std::abs(compute_average(v) - 4.0) < 1e-9);
}

TEST(runner, "compute_average works with a single element") {
    double single[] = {42.0};
    ASSERT_TRUE(std::abs(compute_average(single) - 42.0) < 1e-9);
}

TEST(runner, "from_vector returns average of {1,2,3,4,5}") {
    ASSERT_TRUE(std::abs(from_vector() - 3.0) < 1e-9);
}

TEST(runner, "from_c_array returns average of {10,20,30}") {
    ASSERT_TRUE(std::abs(from_c_array() - 20.0) < 1e-9);
}

TEST(runner, "from_std_array returns average of {2.5,5.0,7.5,10.0}") {
    ASSERT_TRUE(std::abs(from_std_array() - 6.25) < 1e-9);
}

TESTKIT_MAIN(runner)
