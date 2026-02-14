// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex02.h"

static testkit::TestRunner runner("01-03-ex02: Fix a Parameter Type");

TEST(runner, "greet returns Hello greeting") {
    ASSERT_EQ(greet("World"), std::string("Hello, World!"));
    ASSERT_EQ(greet("C++"), std::string("Hello, C++!"));
}

TEST(runner, "greet does not modify the original string") {
    std::string name = "Alice";
    std::string result = greet(name);
    ASSERT_EQ(name, std::string("Alice"));
    ASSERT_EQ(result, std::string("Hello, Alice!"));
}

TEST(runner, "full_greeting combines first and last name") {
    ASSERT_EQ(full_greeting("Jane", "Doe"), std::string("Hello, Jane Doe!"));
}

TEST(runner, "full_greeting does not modify the original strings") {
    std::string first = "John";
    std::string last = "Smith";
    std::string result = full_greeting(first, last);
    ASSERT_EQ(first, std::string("John"));
    ASSERT_EQ(last, std::string("Smith"));
    ASSERT_EQ(result, std::string("Hello, John Smith!"));
}

TESTKIT_MAIN(runner)
