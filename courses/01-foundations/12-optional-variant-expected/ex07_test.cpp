// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-12-ex07: Error Handling with Expected");

TEST(runner, "Expected has_value returns true for success") {
    auto result = make_success<int, std::string>(42);
    ASSERT_TRUE(result.has_value());
}

TEST(runner, "Expected has_value returns false for error") {
    auto result = make_error<int, std::string>("oops");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "Expected value returns the success value") {
    auto result = make_success<int, std::string>(99);
    ASSERT_EQ(result.value(), 99);
}

TEST(runner, "Expected value throws on error") {
    auto result = make_error<int, std::string>("bad");
    bool threw = false;
    try {
        result.value();
    } catch (const std::runtime_error& e) {
        threw = true;
    }
    ASSERT_TRUE(threw);
}

TEST(runner, "Expected error returns the error value") {
    auto result = make_error<int, std::string>("fail");
    ASSERT_EQ(result.error(), std::string("fail"));
}

TEST(runner, "Expected error throws on success") {
    auto result = make_success<int, std::string>(1);
    ASSERT_THROWS(result.error(), std::logic_error);
}

TEST(runner, "Expected value_or returns value when present") {
    auto result = make_success<int, std::string>(10);
    ASSERT_EQ(result.value_or(0), 10);
}

TEST(runner, "Expected value_or returns default on error") {
    auto result = make_error<int, std::string>("oops");
    ASSERT_EQ(result.value_or(-1), -1);
}

TEST(runner, "parse_int succeeds for valid integers") {
    auto r1 = parse_int("42");
    ASSERT_TRUE(r1.has_value());
    ASSERT_EQ(r1.value(), 42);

    auto r2 = parse_int("-7");
    ASSERT_TRUE(r2.has_value());
    ASSERT_EQ(r2.value(), -7);

    auto r3 = parse_int("0");
    ASSERT_TRUE(r3.has_value());
    ASSERT_EQ(r3.value(), 0);
}

TEST(runner, "parse_int returns error for empty input") {
    auto result = parse_int("");
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), std::string("empty input"));
}

TEST(runner, "parse_int returns error for non-numeric input") {
    auto result = parse_int("abc");
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), std::string("invalid integer: abc"));
}

TEST(runner, "parse_int returns error for mixed input") {
    auto result = parse_int("12abc");
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), std::string("invalid integer: 12abc"));
}

TESTKIT_MAIN(runner)
