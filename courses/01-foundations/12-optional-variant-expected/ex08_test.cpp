// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-12-ex08: Expected Chaining");

TEST(runner, "and_then applies function on success") {
    auto result = make_success<int, std::string>(5);
    auto doubled = and_then(result, [](int n) {
        return make_success<int, std::string>(n * 2);
    });
    ASSERT_TRUE(doubled.has_value());
    ASSERT_EQ(doubled.value(), 10);
}

TEST(runner, "and_then propagates error") {
    auto result = make_error<int, std::string>("bad input");
    auto doubled = and_then(result, [](int n) {
        return make_success<int, std::string>(n * 2);
    });
    ASSERT_FALSE(doubled.has_value());
    ASSERT_EQ(doubled.error(), std::string("bad input"));
}

TEST(runner, "validate_positive succeeds for positive numbers") {
    auto r = validate_positive(5);
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r.value(), 5);
}

TEST(runner, "validate_positive fails for zero") {
    auto r = validate_positive(0);
    ASSERT_FALSE(r.has_value());
    ASSERT_EQ(r.error(), std::string("not positive: 0"));
}

TEST(runner, "validate_positive fails for negative numbers") {
    auto r = validate_positive(-3);
    ASSERT_FALSE(r.has_value());
    ASSERT_EQ(r.error(), std::string("not positive: -3"));
}

TEST(runner, "double_value always succeeds") {
    auto r = double_value(7);
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r.value(), 14);
}

TEST(runner, "validate_and_double succeeds for valid positive integers") {
    auto r = validate_and_double("5");
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r.value(), 10);

    auto r2 = validate_and_double("100");
    ASSERT_TRUE(r2.has_value());
    ASSERT_EQ(r2.value(), 200);
}

TEST(runner, "validate_and_double fails for non-numeric input") {
    auto r = validate_and_double("abc");
    ASSERT_FALSE(r.has_value());
    ASSERT_EQ(r.error(), std::string("invalid integer: abc"));
}

TEST(runner, "validate_and_double fails for non-positive input") {
    auto r = validate_and_double("0");
    ASSERT_FALSE(r.has_value());
    ASSERT_EQ(r.error(), std::string("not positive: 0"));

    auto r2 = validate_and_double("-5");
    ASSERT_FALSE(r2.has_value());
    ASSERT_EQ(r2.error(), std::string("not positive: -5"));
}

TEST(runner, "validate_and_double fails for empty input") {
    auto r = validate_and_double("");
    ASSERT_FALSE(r.has_value());
    ASSERT_EQ(r.error(), std::string("empty input"));
}

TESTKIT_MAIN(runner)
