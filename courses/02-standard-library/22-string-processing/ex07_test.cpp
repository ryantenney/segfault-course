// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("02-22-ex07: Simple Regex Match");

TEST(runner, "is_valid_identifier accepts simple name") {
    ASSERT_TRUE(is_valid_identifier("counter"));
}

TEST(runner, "is_valid_identifier accepts underscore prefix") {
    ASSERT_TRUE(is_valid_identifier("_private"));
}

TEST(runner, "is_valid_identifier accepts letters and digits") {
    ASSERT_TRUE(is_valid_identifier("var42"));
}

TEST(runner, "is_valid_identifier accepts single underscore") {
    ASSERT_TRUE(is_valid_identifier("_"));
}

TEST(runner, "is_valid_identifier rejects leading digit") {
    ASSERT_FALSE(is_valid_identifier("3abc"));
}

TEST(runner, "is_valid_identifier rejects spaces") {
    ASSERT_FALSE(is_valid_identifier("my var"));
}

TEST(runner, "is_valid_identifier rejects empty string") {
    ASSERT_FALSE(is_valid_identifier(""));
}

TEST(runner, "is_valid_identifier rejects hyphens") {
    ASSERT_FALSE(is_valid_identifier("my-var"));
}

TEST(runner, "contains_number finds digits in text") {
    ASSERT_TRUE(contains_number("abc123def"));
}

TEST(runner, "contains_number finds standalone number") {
    ASSERT_TRUE(contains_number("42"));
}

TEST(runner, "contains_number returns false for no digits") {
    ASSERT_FALSE(contains_number("hello world"));
}

TEST(runner, "contains_number returns false for empty") {
    ASSERT_FALSE(contains_number(""));
}

TEST(runner, "is_valid_email_simple accepts basic email") {
    ASSERT_TRUE(is_valid_email_simple("user@example.com"));
}

TEST(runner, "is_valid_email_simple accepts short TLD") {
    ASSERT_TRUE(is_valid_email_simple("alice@host.io"));
}

TEST(runner, "is_valid_email_simple rejects missing @") {
    ASSERT_FALSE(is_valid_email_simple("userexample.com"));
}

TEST(runner, "is_valid_email_simple rejects missing TLD") {
    ASSERT_FALSE(is_valid_email_simple("user@example"));
}

TEST(runner, "is_valid_email_simple rejects empty local part") {
    ASSERT_FALSE(is_valid_email_simple("@example.com"));
}

TEST(runner, "is_valid_email_simple rejects TLD too long") {
    ASSERT_FALSE(is_valid_email_simple("user@host.abcde"));
}

TESTKIT_MAIN(runner)
