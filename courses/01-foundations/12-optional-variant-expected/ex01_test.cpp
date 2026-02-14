// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-12-ex01: Return optional from Lookup");

TEST(runner, "find_user_age returns the age for known users") {
    auto alice = find_user_age("Alice");
    ASSERT_TRUE(alice.has_value());
    ASSERT_EQ(alice.value(), 30);

    auto bob = find_user_age("Bob");
    ASSERT_TRUE(bob.has_value());
    ASSERT_EQ(bob.value(), 25);

    auto charlie = find_user_age("Charlie");
    ASSERT_TRUE(charlie.has_value());
    ASSERT_EQ(charlie.value(), 35);
}

TEST(runner, "find_user_age returns nullopt for unknown users") {
    auto result = find_user_age("Eve");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "find_user_age returns nullopt for empty name") {
    auto result = find_user_age("");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "optional can be tested in boolean context") {
    // An optional with a value is truthy; empty optional is falsy.
    auto found = find_user_age("Alice");
    ASSERT_TRUE(static_cast<bool>(found));

    auto missing = find_user_age("Nobody");
    ASSERT_FALSE(static_cast<bool>(missing));
}

TESTKIT_MAIN(runner)
