// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-13-ex07: Exception vs Error Code");

TEST(runner, "lookup_user_throwing returns name for valid IDs") {
    ASSERT_EQ(lookup_user_throwing(1), std::string("Alice"));
    ASSERT_EQ(lookup_user_throwing(2), std::string("Bob"));
    ASSERT_EQ(lookup_user_throwing(3), std::string("Charlie"));
}

TEST(runner, "lookup_user_throwing throws for invalid IDs") {
    ASSERT_THROWS(lookup_user_throwing(99), std::runtime_error);
}

TEST(runner, "lookup_user_throwing has correct error message") {
    try {
        lookup_user_throwing(42);
        ASSERT_TRUE(false);
    } catch (const std::runtime_error& e) {
        ASSERT_EQ(std::string(e.what()), std::string("user not found: 42"));
    }
}

TEST(runner, "lookup_user_result succeeds for valid IDs") {
    auto r = lookup_user_result(1);
    ASSERT_TRUE(r.found);
    ASSERT_EQ(r.name, std::string("Alice"));
    ASSERT_EQ(r.error_message, std::string(""));
}

TEST(runner, "lookup_user_result fails for invalid IDs") {
    auto r = lookup_user_result(99);
    ASSERT_FALSE(r.found);
    ASSERT_EQ(r.name, std::string(""));
    ASSERT_EQ(r.error_message, std::string("user not found: 99"));
}

TEST(runner, "greet_user_with_exceptions returns greeting for valid ID") {
    ASSERT_EQ(greet_user_with_exceptions(1), std::string("Hello, Alice!"));
    ASSERT_EQ(greet_user_with_exceptions(2), std::string("Hello, Bob!"));
}

TEST(runner, "greet_user_with_exceptions returns error for invalid ID") {
    ASSERT_EQ(greet_user_with_exceptions(99),
              std::string("Error: user not found: 99"));
}

TEST(runner, "greet_user_with_result returns greeting for valid ID") {
    ASSERT_EQ(greet_user_with_result(1), std::string("Hello, Alice!"));
    ASSERT_EQ(greet_user_with_result(3), std::string("Hello, Charlie!"));
}

TEST(runner, "greet_user_with_result returns error for invalid ID") {
    ASSERT_EQ(greet_user_with_result(99),
              std::string("Error: user not found: 99"));
}

TEST(runner, "both approaches produce identical results") {
    for (int id : {1, 2, 3, 42, 99, 0}) {
        ASSERT_EQ(greet_user_with_exceptions(id),
                  greet_user_with_result(id));
    }
}

TESTKIT_MAIN(runner)
