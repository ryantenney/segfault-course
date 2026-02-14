// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

#include <chrono>

static testkit::TestRunner runner("02-21-ex03: Duration Arithmetic");

TEST(runner, "add_durations adds two millisecond values") {
    ASSERT_EQ(add_durations(std::chrono::milliseconds(100),
                            std::chrono::milliseconds(200)), 300LL);
}

TEST(runner, "add_durations with zero") {
    ASSERT_EQ(add_durations(std::chrono::milliseconds(500),
                            std::chrono::milliseconds(0)), 500LL);
}

TEST(runner, "subtract_durations subtracts b from a") {
    ASSERT_EQ(subtract_durations(std::chrono::milliseconds(500),
                                  std::chrono::milliseconds(200)), 300LL);
}

TEST(runner, "subtract_durations can produce negative") {
    ASSERT_EQ(subtract_durations(std::chrono::milliseconds(100),
                                  std::chrono::milliseconds(300)), -200LL);
}

TEST(runner, "mixed_add converts seconds to ms and adds") {
    ASSERT_EQ(mixed_add(std::chrono::seconds(2),
                        std::chrono::milliseconds(500)), 2500LL);
}

TEST(runner, "mixed_add with zero seconds") {
    ASSERT_EQ(mixed_add(std::chrono::seconds(0),
                        std::chrono::milliseconds(750)), 750LL);
}

TEST(runner, "scale_duration multiplies by factor") {
    ASSERT_EQ(scale_duration(std::chrono::milliseconds(100), 5), 500LL);
}

TEST(runner, "scale_duration with factor zero") {
    ASSERT_EQ(scale_duration(std::chrono::milliseconds(999), 0), 0LL);
}

TEST(runner, "remaining_ms computes what's left") {
    ASSERT_EQ(remaining_ms(std::chrono::seconds(5),
                           std::chrono::milliseconds(3200)), 1800LL);
}

TEST(runner, "remaining_ms returns 0 when elapsed exceeds total") {
    ASSERT_EQ(remaining_ms(std::chrono::seconds(2),
                           std::chrono::milliseconds(5000)), 0LL);
}

TEST(runner, "remaining_ms with exact match returns 0") {
    ASSERT_EQ(remaining_ms(std::chrono::seconds(3),
                           std::chrono::milliseconds(3000)), 0LL);
}

TESTKIT_MAIN(runner)
