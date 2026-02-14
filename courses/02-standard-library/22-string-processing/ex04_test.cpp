// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("02-22-ex04: Format Strings");

TEST(runner, "greet formats name and age") {
    ASSERT_EQ(greet("Alice", 30),
              std::string("Hello, Alice! You are 30 years old."));
}

TEST(runner, "greet with different values") {
    ASSERT_EQ(greet("Bob", 7),
              std::string("Hello, Bob! You are 7 years old."));
}

TEST(runner, "format_price with whole dollars") {
    ASSERT_EQ(format_price(10.0), std::string("$10.00"));
}

TEST(runner, "format_price with cents") {
    ASSERT_EQ(format_price(12.5), std::string("$12.50"));
}

TEST(runner, "format_price with small amount") {
    ASSERT_EQ(format_price(0.99), std::string("$0.99"));
}

TEST(runner, "format_price with precise cents") {
    ASSERT_EQ(format_price(7.1), std::string("$7.10"));
}

TEST(runner, "format_table_row basic") {
    std::string row = format_table_row("Alice", 100);
    // "Alice               " (20 chars) + " " + "  100" (5 chars)
    ASSERT_EQ(row, std::string("Alice                  100"));
}

TEST(runner, "format_table_row long name") {
    std::string row = format_table_row("Bartholomew", 42);
    ASSERT_EQ(row, std::string("Bartholomew             42"));
}

TEST(runner, "format_table_row short score") {
    std::string row = format_table_row("Zoe", 5);
    ASSERT_EQ(row, std::string("Zoe                      5"));
}

TESTKIT_MAIN(runner)
