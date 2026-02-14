// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

#include <chrono>

static testkit::TestRunner runner("02-21-ex02: Duration Types");

TEST(runner, "to_milliseconds converts seconds to ms") {
    ASSERT_EQ(to_milliseconds(std::chrono::seconds(3)), 3000LL);
}

TEST(runner, "to_milliseconds of zero seconds is zero") {
    ASSERT_EQ(to_milliseconds(std::chrono::seconds(0)), 0LL);
}

TEST(runner, "to_seconds truncates milliseconds") {
    ASSERT_EQ(to_seconds(std::chrono::milliseconds(2500)), 2LL);
}

TEST(runner, "to_seconds of exact conversion") {
    ASSERT_EQ(to_seconds(std::chrono::milliseconds(4000)), 4LL);
}

TEST(runner, "to_seconds of sub-second value") {
    ASSERT_EQ(to_seconds(std::chrono::milliseconds(999)), 0LL);
}

TEST(runner, "to_minutes truncates seconds") {
    ASSERT_EQ(to_minutes(std::chrono::seconds(150)), 2LL);
}

TEST(runner, "to_minutes of exact minutes") {
    ASSERT_EQ(to_minutes(std::chrono::seconds(120)), 2LL);
}

TEST(runner, "total_ms combines hours, minutes, and seconds") {
    auto h = std::chrono::hours(1);
    auto m = std::chrono::minutes(30);
    auto s = std::chrono::seconds(15);
    // 1h = 3600000ms, 30m = 1800000ms, 15s = 15000ms = 5415000ms
    ASSERT_EQ(total_ms(h, m, s), 5415000LL);
}

TEST(runner, "total_ms with all zeros") {
    ASSERT_EQ(total_ms(std::chrono::hours(0), std::chrono::minutes(0),
                        std::chrono::seconds(0)), 0LL);
}

TEST(runner, "total_ms with only seconds") {
    ASSERT_EQ(total_ms(std::chrono::hours(0), std::chrono::minutes(0),
                        std::chrono::seconds(5)), 5000LL);
}

TESTKIT_MAIN(runner)
