// Exercise 08 -- Tests (read-only)
//
// Verifies the full pipeline chains parse, validate, double, and format.

#include <testkit/testkit.h>
#include "ex08.h"

#include <string>

static testkit::TestRunner runner("05-51-ex08: Pipeline with Results");

// --- Individual step tests ---

TEST(runner, "parse_int succeeds on valid integer string") {
    auto r = parse_int("42");
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), 42);
}

TEST(runner, "parse_int fails on non-numeric string") {
    auto r = parse_int("abc");
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "parse_int fails on empty string") {
    auto r = parse_int("");
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "validate_range succeeds when in range") {
    auto r = validate_range(50, 1, 100);
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), 50);
}

TEST(runner, "validate_range fails below minimum") {
    auto r = validate_range(0, 1, 100);
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "validate_range fails above maximum") {
    auto r = validate_range(101, 1, 100);
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "double_value doubles the input") {
    auto r = double_value(21);
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), 42);
}

TEST(runner, "format_output produces expected string") {
    auto r = format_output(42);
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), std::string("result: 42"));
}

// --- Full pipeline tests ---

TEST(runner, "pipeline succeeds end to end") {
    auto r = run_pipeline("25");
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), std::string("result: 50"));
}

TEST(runner, "pipeline fails at parse step") {
    auto r = run_pipeline("not_a_number");
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "pipeline fails at validate step (too low)") {
    auto r = run_pipeline("0");
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "pipeline fails at validate step (too high)") {
    auto r = run_pipeline("200");
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "pipeline with boundary value 1") {
    auto r = run_pipeline("1");
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), std::string("result: 2"));
}

TEST(runner, "pipeline with boundary value 100") {
    auto r = run_pipeline("100");
    ASSERT_TRUE(r.is_ok());
    ASSERT_EQ(r.value(), std::string("result: 200"));
}

TESTKIT_MAIN(runner)
