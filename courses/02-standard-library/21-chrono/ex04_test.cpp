// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

#include <chrono>

static testkit::TestRunner runner("02-21-ex04: Timeout Check");

TEST(runner, "is_expired returns true when now is past deadline") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::seconds(5);
    auto now = base + std::chrono::seconds(6);
    ASSERT_TRUE(is_expired(now, deadline));
}

TEST(runner, "is_expired returns true when now equals deadline") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::seconds(5);
    ASSERT_TRUE(is_expired(deadline, deadline));
}

TEST(runner, "is_expired returns false when now is before deadline") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::seconds(5);
    auto now = base + std::chrono::seconds(3);
    ASSERT_FALSE(is_expired(now, deadline));
}

TEST(runner, "time_remaining_ms returns remaining time") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::milliseconds(5000);
    auto now = base + std::chrono::milliseconds(3200);
    ASSERT_EQ(time_remaining_ms(now, deadline), 1800LL);
}

TEST(runner, "time_remaining_ms returns 0 when expired") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::seconds(2);
    auto now = base + std::chrono::seconds(5);
    ASSERT_EQ(time_remaining_ms(now, deadline), 0LL);
}

TEST(runner, "time_remaining_ms returns 0 when exactly at deadline") {
    auto base = SteadyTimePoint{};
    auto deadline = base + std::chrono::seconds(3);
    ASSERT_EQ(time_remaining_ms(deadline, deadline), 0LL);
}

TEST(runner, "make_deadline computes start + timeout") {
    auto start = SteadyTimePoint{} + std::chrono::seconds(10);
    auto timeout = std::chrono::milliseconds(2500);
    auto deadline = make_deadline(start, timeout);
    auto expected = start + timeout;
    ASSERT_TRUE(deadline == expected);
}

TEST(runner, "extend_deadline adds extra time") {
    auto deadline = SteadyTimePoint{} + std::chrono::seconds(10);
    auto extra = std::chrono::milliseconds(3000);
    auto extended = extend_deadline(deadline, extra);
    auto expected = deadline + extra;
    ASSERT_TRUE(extended == expected);
}

TEST(runner, "extend_deadline with zero extra returns same deadline") {
    auto deadline = SteadyTimePoint{} + std::chrono::seconds(10);
    auto extended = extend_deadline(deadline, std::chrono::milliseconds(0));
    ASSERT_TRUE(extended == deadline);
}

TESTKIT_MAIN(runner)
