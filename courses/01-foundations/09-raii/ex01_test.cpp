// Exercise 01 — Tests (read-only)
//
// Verifies the ScopedTimer RAII class.

#include <chrono>
#include <thread>
#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("01-09-ex01: Scoped Timer");

TEST(runner, "elapsed_ms starts near zero") {
    double result = -1.0;
    ScopedTimer timer(result);
    double early = timer.elapsed_ms();
    // Should be very small (less than 100ms for sure)
    ASSERT_TRUE(early >= 0.0);
    ASSERT_TRUE(early < 100.0);
}

TEST(runner, "elapsed_ms increases over time") {
    double result = -1.0;
    ScopedTimer timer(result);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    double elapsed = timer.elapsed_ms();
    // Should be at least 20ms (generous margin for CI)
    ASSERT_TRUE(elapsed >= 20.0);
}

TEST(runner, "destructor writes elapsed time to output") {
    double result = -1.0;
    {
        ScopedTimer timer(result);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // After scope exit, result should be populated
    ASSERT_TRUE(result >= 20.0);
    // Sanity check: shouldn't be absurdly large
    ASSERT_TRUE(result < 5000.0);
}

TESTKIT_MAIN(runner)
