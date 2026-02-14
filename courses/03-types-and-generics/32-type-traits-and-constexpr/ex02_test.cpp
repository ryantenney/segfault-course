// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("03-32-ex02: if constexpr Branching");

TEST(runner, "stringify converts int to string") {
    ASSERT_EQ(stringify(42), std::string("42"));
}

TEST(runner, "stringify converts double to string") {
    // std::to_string(3.14) may produce "3.140000", just check prefix
    std::string result = stringify(3.14);
    ASSERT_TRUE(result.substr(0, 4) == "3.14");
}

TEST(runner, "stringify passes through std::string") {
    std::string s = "hello";
    ASSERT_EQ(stringify(s), std::string("hello"));
}

TEST(runner, "stringify returns (unknown) for non-arithmetic non-string") {
    struct Widget {};
    Widget w;
    ASSERT_EQ(stringify(w), std::string("(unknown)"));
}

TEST(runner, "default_value<int> returns 0") {
    ASSERT_EQ(default_value<int>(), 0);
}

TEST(runner, "default_value<double> returns 0.0") {
    ASSERT_EQ(default_value<double>(), 0.0);
}

TEST(runner, "default_value<std::string> returns empty string") {
    ASSERT_EQ(default_value<std::string>(), std::string(""));
}

TESTKIT_MAIN(runner)
