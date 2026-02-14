// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

#include <cstdint>

static testkit::TestRunner runner("01-05-ex02: Enum with Explicit Underlying Type");

TEST(runner, "Severity has uint8_t underlying type") {
    severity_value(Severity::Trace); // gates on TODO()
    // sizeof(uint8_t) is 1. If the underlying type is correct, Severity is 1 byte.
    ASSERT_EQ(sizeof(Severity), sizeof(uint8_t));
}

TEST(runner, "Severity values match expected integers") {
    ASSERT_EQ(severity_value(Severity::Trace), uint8_t(0));
    ASSERT_EQ(severity_value(Severity::Debug), uint8_t(1));
    ASSERT_EQ(severity_value(Severity::Info), uint8_t(2));
    ASSERT_EQ(severity_value(Severity::Warning), uint8_t(3));
    ASSERT_EQ(severity_value(Severity::Error), uint8_t(4));
    ASSERT_EQ(severity_value(Severity::Fatal), uint8_t(5));
}

TEST(runner, "is_warning_or_above filters correctly") {
    ASSERT_FALSE(is_warning_or_above(Severity::Trace));
    ASSERT_FALSE(is_warning_or_above(Severity::Debug));
    ASSERT_FALSE(is_warning_or_above(Severity::Info));
    ASSERT_TRUE(is_warning_or_above(Severity::Warning));
    ASSERT_TRUE(is_warning_or_above(Severity::Error));
    ASSERT_TRUE(is_warning_or_above(Severity::Fatal));
}

TEST(runner, "more_severe compares severity levels") {
    ASSERT_TRUE(more_severe(Severity::Fatal, Severity::Error));
    ASSERT_TRUE(more_severe(Severity::Error, Severity::Info));
    ASSERT_FALSE(more_severe(Severity::Info, Severity::Error));
    ASSERT_FALSE(more_severe(Severity::Warning, Severity::Warning));
}

TESTKIT_MAIN(runner)
