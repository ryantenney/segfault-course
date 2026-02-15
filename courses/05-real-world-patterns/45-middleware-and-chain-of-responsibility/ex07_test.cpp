// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include <chrono>
#include <thread>
#include "ex07.h"

static testkit::TestRunner runner("05-45-ex07: Timing Middleware");

TEST(runner, "timing middleware records non-negative time") {
    double elapsed = -1.0;
    auto timer = make_timing_middleware(elapsed);
    std::string ctx;
    timer(ctx, []() {});
    ASSERT_TRUE(elapsed >= 0.0);
}

TEST(runner, "timing middleware records time for slow operation") {
    double elapsed = 0.0;
    auto timer = make_timing_middleware(elapsed);
    std::string ctx;
    timer(ctx, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    });
    // Should be at least 15ms (allowing some scheduling slack)
    ASSERT_TRUE(elapsed >= 15.0);
}

TEST(runner, "timing middleware does not alter context") {
    double elapsed = 0.0;
    auto timer = make_timing_middleware(elapsed);
    std::string ctx = "unchanged";
    timer(ctx, []() {});
    ASSERT_EQ(ctx, std::string("unchanged"));
}

TEST(runner, "timing middleware still calls next") {
    double elapsed = 0.0;
    auto timer = make_timing_middleware(elapsed);
    std::string ctx;
    bool next_called = false;
    timer(ctx, [&next_called]() { next_called = true; });
    ASSERT_TRUE(next_called);
}

TESTKIT_MAIN(runner)
