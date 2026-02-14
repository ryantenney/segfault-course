// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex07.h"

#include <chrono>
#include <vector>

static testkit::TestRunner runner("02-21-ex07: Sleep with Chrono");

TEST(runner, "make_sleep_duration creates correct duration") {
    auto d = make_sleep_duration(250);
    ASSERT_EQ(d.count(), 250LL);
}

TEST(runner, "make_sleep_duration with zero") {
    auto d = make_sleep_duration(0);
    ASSERT_EQ(d.count(), 0LL);
}

TEST(runner, "make_sleep_duration with large value") {
    auto d = make_sleep_duration(5000);
    ASSERT_EQ(d.count(), 5000LL);
}

TEST(runner, "compute_wake_time returns now + sleep_duration") {
    auto now = SteadyTimePoint{} + std::chrono::seconds(100);
    auto duration = std::chrono::milliseconds(500);
    auto wake = compute_wake_time(now, duration);
    auto expected = now + duration;
    ASSERT_TRUE(wake == expected);
}

TEST(runner, "compute_wake_time with zero sleep returns now") {
    auto now = SteadyTimePoint{} + std::chrono::seconds(50);
    auto wake = compute_wake_time(now, std::chrono::milliseconds(0));
    ASSERT_TRUE(wake == now);
}

TEST(runner, "sleep_durations converts vector of ints") {
    std::vector<int> values = {100, 200, 300};
    auto durations = sleep_durations(values);
    ASSERT_EQ(durations.size(), 3u);
    ASSERT_EQ(durations[0].count(), 100LL);
    ASSERT_EQ(durations[1].count(), 200LL);
    ASSERT_EQ(durations[2].count(), 300LL);
}

TEST(runner, "sleep_durations with empty vector") {
    std::vector<int> values;
    auto durations = sleep_durations(values);
    ASSERT_EQ(durations.size(), 0u);
}

TEST(runner, "total_sleep_ms sums all durations") {
    std::vector<std::chrono::milliseconds> durations = {
        std::chrono::milliseconds(100),
        std::chrono::milliseconds(250),
        std::chrono::milliseconds(50),
    };
    ASSERT_EQ(total_sleep_ms(durations), 400LL);
}

TEST(runner, "total_sleep_ms with empty vector returns 0") {
    std::vector<std::chrono::milliseconds> durations;
    ASSERT_EQ(total_sleep_ms(durations), 0LL);
}

TEST(runner, "total_sleep_ms with single duration") {
    std::vector<std::chrono::milliseconds> durations = {
        std::chrono::milliseconds(999),
    };
    ASSERT_EQ(total_sleep_ms(durations), 999LL);
}

TESTKIT_MAIN(runner)
