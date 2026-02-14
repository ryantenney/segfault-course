// Exercise 06 -- Tests (read-only)
//
// Verifies that non-template overloads are preferred over template
// specializations.

#include <string>
#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("03-29-ex06: Overload vs Specialization");

TEST(runner, "template handles int") {
    ASSERT_EQ(format_value(42), std::string("value: 42"));
}

TEST(runner, "template handles negative int") {
    ASSERT_EQ(format_value(-5), std::string("value: -5"));
}

TEST(runner, "template handles double") {
    std::string result = format_value(3.14);
    ASSERT_TRUE(result.find("value: 3.14") == 0u);
}

TEST(runner, "overload handles const char*") {
    ASSERT_EQ(format_value("hello"), std::string("text: hello"));
}

TEST(runner, "overload handles std::string") {
    std::string s = "world";
    ASSERT_EQ(format_value(s), std::string("text: world"));
}

TEST(runner, "overload handles empty string") {
    ASSERT_EQ(format_value(""), std::string("text: "));
}

TEST(runner, "const char* calls overload not template") {
    // If the template were called instead of the overload, it would
    // try to call std::to_string on a pointer, which wouldn't compile.
    // The fact that this compiles proves the overload is selected.
    std::string result = format_value("test");
    ASSERT_TRUE(result.find("text:") == 0u);
}

TEST(runner, "std::string calls overload not template") {
    std::string s = "check";
    std::string result = format_value(s);
    ASSERT_TRUE(result.find("text:") == 0u);
}

TESTKIT_MAIN(runner)
