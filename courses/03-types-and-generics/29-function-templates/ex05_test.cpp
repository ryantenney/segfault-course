// Exercise 05 -- Tests (read-only)
//
// Verifies explicit template specialization for stringify.

#include <string>
#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("03-29-ex05: Explicit Specialization");

TEST(runner, "stringify int") {
    ASSERT_EQ(stringify(42), std::string("42"));
}

TEST(runner, "stringify negative int") {
    ASSERT_EQ(stringify(-7), std::string("-7"));
}

TEST(runner, "stringify double") {
    // std::to_string for doubles includes trailing zeros
    std::string result = stringify(3.14);
    // Just check it starts with "3.14"
    ASSERT_TRUE(result.find("3.14") == 0u);
}

TEST(runner, "stringify string wraps in quotes") {
    ASSERT_EQ(stringify(std::string("hello")), std::string("\"hello\""));
}

TEST(runner, "stringify empty string wraps in quotes") {
    ASSERT_EQ(stringify(std::string("")), std::string("\"\""));
}

TEST(runner, "stringify string with spaces") {
    ASSERT_EQ(stringify(std::string("hello world")),
              std::string("\"hello world\""));
}

TEST(runner, "stringify bool true") {
    ASSERT_EQ(stringify(true), std::string("true"));
}

TEST(runner, "stringify bool false") {
    ASSERT_EQ(stringify(false), std::string("false"));
}

TESTKIT_MAIN(runner)
