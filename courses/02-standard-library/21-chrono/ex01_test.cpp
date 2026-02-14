// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

#include <chrono>

static testkit::TestRunner runner("02-21-ex01: Measure Elapsed Time");

TEST(runner, "elapsed_ms computes milliseconds between two time points") {
    auto start = SteadyTimePoint{};
    auto end = start + std::chrono::milliseconds(1500);
    ASSERT_EQ(elapsed_ms(start, end), 1500LL);
}

TEST(runner, "elapsed_ms returns zero for same time point") {
    auto t = SteadyTimePoint{};
    ASSERT_EQ(elapsed_ms(t, t), 0LL);
}

TEST(runner, "elapsed_us computes microseconds between two time points") {
    auto start = SteadyTimePoint{};
    auto end = start + std::chrono::microseconds(2500);
    ASSERT_EQ(elapsed_us(start, end), 2500LL);
}

TEST(runner, "elapsed_us for a duration in milliseconds") {
    auto start = SteadyTimePoint{};
    auto end = start + std::chrono::milliseconds(3);
    ASSERT_EQ(elapsed_us(start, end), 3000LL);
}

TEST(runner, "elapsed_between adds offset to start") {
    auto start = SteadyTimePoint{};
    auto offset = std::chrono::milliseconds(500);
    auto result = elapsed_between(start, offset);
    auto expected = start + offset;
    ASSERT_TRUE(result == expected);
}

TEST(runner, "elapsed_between with zero offset returns start") {
    auto start = SteadyTimePoint{} + std::chrono::seconds(10);
    auto result = elapsed_between(start, std::chrono::milliseconds(0));
    ASSERT_TRUE(result == start);
}

TESTKIT_MAIN(runner)
