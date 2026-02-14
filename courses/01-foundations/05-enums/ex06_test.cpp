// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-05-ex06: Scoped Enum in Switch");

TEST(runner, "method_name returns the uppercase name") {
    ASSERT_EQ(method_name(HttpMethod::Get), std::string_view("GET"));
    ASSERT_EQ(method_name(HttpMethod::Post), std::string_view("POST"));
    ASSERT_EQ(method_name(HttpMethod::Put), std::string_view("PUT"));
    ASSERT_EQ(method_name(HttpMethod::Delete), std::string_view("DELETE"));
}

TEST(runner, "is_safe identifies safe methods") {
    ASSERT_TRUE(is_safe(HttpMethod::Get));
    ASSERT_FALSE(is_safe(HttpMethod::Post));
    ASSERT_FALSE(is_safe(HttpMethod::Put));
    ASSERT_FALSE(is_safe(HttpMethod::Delete));
}

TEST(runner, "is_idempotent identifies idempotent methods") {
    ASSERT_TRUE(is_idempotent(HttpMethod::Get));
    ASSERT_FALSE(is_idempotent(HttpMethod::Post));
    ASSERT_TRUE(is_idempotent(HttpMethod::Put));
    ASSERT_TRUE(is_idempotent(HttpMethod::Delete));
}

TESTKIT_MAIN(runner)
