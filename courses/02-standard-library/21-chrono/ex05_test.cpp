// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

#include <chrono>
#include <vector>

static testkit::TestRunner runner("02-21-ex05: Periodic Timer Logic");

TEST(runner, "compute_fire_times fires at each interval") {
    auto base = SteadyTimePoint{};
    auto interval = std::chrono::milliseconds(100);

    std::vector<SteadyTimePoint> timestamps = {
        base + std::chrono::milliseconds(50),   // before first fire
        base + std::chrono::milliseconds(100),  // fire 1
        base + std::chrono::milliseconds(150),  // between fires
        base + std::chrono::milliseconds(200),  // fire 2
        base + std::chrono::milliseconds(300),  // fire 3
    };

    auto fires = compute_fire_times(base, interval, timestamps);
    ASSERT_EQ(fires.size(), 3u);
    ASSERT_TRUE(fires[0] == base + std::chrono::milliseconds(100));
    ASSERT_TRUE(fires[1] == base + std::chrono::milliseconds(200));
    ASSERT_TRUE(fires[2] == base + std::chrono::milliseconds(300));
}

TEST(runner, "compute_fire_times handles timestamps that skip intervals") {
    auto base = SteadyTimePoint{};
    auto interval = std::chrono::milliseconds(100);

    std::vector<SteadyTimePoint> timestamps = {
        base + std::chrono::milliseconds(250),  // skips first two intervals
    };

    // At 250ms, next_fire is 100ms. 250 >= 100, fire. Advance to 200. 250 >= 200, advance to 300.
    // The timestamp 250 is included once.
    auto fires = compute_fire_times(base, interval, timestamps);
    ASSERT_EQ(fires.size(), 1u);
    ASSERT_TRUE(fires[0] == base + std::chrono::milliseconds(250));
}

TEST(runner, "compute_fire_times with empty timestamps returns empty") {
    auto base = SteadyTimePoint{};
    auto interval = std::chrono::milliseconds(100);
    std::vector<SteadyTimePoint> timestamps;
    auto fires = compute_fire_times(base, interval, timestamps);
    ASSERT_EQ(fires.size(), 0u);
}

TEST(runner, "compute_fire_times all timestamps before first fire") {
    auto base = SteadyTimePoint{};
    auto interval = std::chrono::milliseconds(1000);

    std::vector<SteadyTimePoint> timestamps = {
        base + std::chrono::milliseconds(100),
        base + std::chrono::milliseconds(500),
        base + std::chrono::milliseconds(999),
    };

    auto fires = compute_fire_times(base, interval, timestamps);
    ASSERT_EQ(fires.size(), 0u);
}

TEST(runner, "count_intervals counts complete intervals") {
    auto base = SteadyTimePoint{};
    auto start = base;
    auto end = base + std::chrono::milliseconds(550);
    ASSERT_EQ(count_intervals(start, end, std::chrono::milliseconds(100)), 5);
}

TEST(runner, "count_intervals with exact multiple") {
    auto base = SteadyTimePoint{};
    auto start = base;
    auto end = base + std::chrono::milliseconds(300);
    ASSERT_EQ(count_intervals(start, end, std::chrono::milliseconds(100)), 3);
}

TEST(runner, "count_intervals returns 0 when end <= start") {
    auto base = SteadyTimePoint{};
    ASSERT_EQ(count_intervals(base, base, std::chrono::milliseconds(100)), 0);
}

TEST(runner, "count_intervals returns 0 for sub-interval duration") {
    auto base = SteadyTimePoint{};
    auto start = base;
    auto end = base + std::chrono::milliseconds(50);
    ASSERT_EQ(count_intervals(start, end, std::chrono::milliseconds(100)), 0);
}

TEST(runner, "next_fire_time computes last_fire + interval") {
    auto base = SteadyTimePoint{} + std::chrono::seconds(5);
    auto interval = std::chrono::milliseconds(250);
    auto result = next_fire_time(base, interval);
    auto expected = base + interval;
    ASSERT_TRUE(result == expected);
}

TESTKIT_MAIN(runner)
