// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

#include <cmath>

static testkit::TestRunner runner("02-20-ex02: Functor Class");

TEST(runner, "initial count is zero") {
    RunningAverage avg;
    ASSERT_EQ(avg.count(), 0);
}

TEST(runner, "initial average is 0.0") {
    RunningAverage avg;
    avg.count();  // gate: triggers TODO() if not implemented
    ASSERT_TRUE(std::abs(avg.average() - 0.0) < 1e-9);
}

TEST(runner, "single value returns that value as average") {
    RunningAverage avg;
    double result = avg(10.0);
    ASSERT_TRUE(std::abs(result - 10.0) < 1e-9);
    ASSERT_EQ(avg.count(), 1);
}

TEST(runner, "multiple values compute running average") {
    RunningAverage avg;
    avg(10.0);
    avg(20.0);
    double result = avg(30.0);
    ASSERT_TRUE(std::abs(result - 20.0) < 1e-9);
    ASSERT_EQ(avg.count(), 3);
}

TEST(runner, "average() matches operator() return value") {
    RunningAverage avg;
    avg(4.0);
    avg(8.0);
    double from_call = avg(12.0);
    double from_method = avg.average();
    ASSERT_TRUE(std::abs(from_call - from_method) < 1e-9);
    ASSERT_TRUE(std::abs(from_method - 8.0) < 1e-9);
}

TESTKIT_MAIN(runner)
