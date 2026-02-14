// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex06.h"

#include <chrono>
#include <string>

static testkit::TestRunner runner("02-21-ex06: Format a Timestamp");

// Helper: create a time_point from a known time_t value.
static SystemTimePoint tp_from_time_t(std::time_t t) {
    return std::chrono::system_clock::from_time_t(t);
}

TEST(runner, "format_utc formats epoch as 1970-01-01 00:00:00") {
    auto tp = tp_from_time_t(0);
    ASSERT_EQ(format_utc(tp), std::string("1970-01-01 00:00:00"));
}

TEST(runner, "format_utc formats Y2K as 2000-01-01 00:00:00") {
    // 2000-01-01 00:00:00 UTC = time_t 946684800
    auto tp = tp_from_time_t(946684800);
    ASSERT_EQ(format_utc(tp), std::string("2000-01-01 00:00:00"));
}

TEST(runner, "format_utc formats one day after epoch") {
    // 1970-01-02 00:00:00 UTC = time_t 86400
    auto tp = tp_from_time_t(86400);
    ASSERT_EQ(format_utc(tp), std::string("1970-01-02 00:00:00"));
}

TEST(runner, "format_date_only formats epoch date") {
    auto tp = tp_from_time_t(0);
    ASSERT_EQ(format_date_only(tp), std::string("1970-01-01"));
}

TEST(runner, "format_date_only formats Y2K date") {
    // 2000-01-01 00:00:00 UTC = time_t 946684800
    auto tp = tp_from_time_t(946684800);
    ASSERT_EQ(format_date_only(tp), std::string("2000-01-01"));
}

TEST(runner, "to_time_t_value returns correct value for epoch") {
    auto tp = tp_from_time_t(0);
    ASSERT_EQ(to_time_t_value(tp), static_cast<std::time_t>(0));
}

TEST(runner, "to_time_t_value round-trips a known time_t") {
    std::time_t known = 946684800;
    auto tp = tp_from_time_t(known);
    ASSERT_EQ(to_time_t_value(tp), known);
}

TESTKIT_MAIN(runner)
