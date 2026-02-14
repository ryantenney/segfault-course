// Exercise 01 -- Tests (read-only)
//
// Verifies the Numeric concept and constrained functions.

#include <testkit/testkit.h>
#include <type_traits>
#include "ex01.h"

static testkit::TestRunner runner("03-31-ex01: Simple Concept");

TEST(runner, "add works with int") {
    ASSERT_EQ(add(3, 4), 7);
}

TEST(runner, "add works with double") {
    double result = add(1.5, 2.5);
    ASSERT_TRUE(result == 4.0);
}

TEST(runner, "multiply works with int") {
    ASSERT_EQ(multiply(3, 4), 12);
}

TEST(runner, "multiply works with double") {
    double result = multiply(2.5, 4.0);
    ASSERT_TRUE(result == 10.0);
}

TEST(runner, "add works with float") {
    float result = add(1.0f, 2.0f);
    ASSERT_TRUE(result == 3.0f);
}

TEST(runner, "Numeric concept accepts arithmetic types") {
    // Gate: add must work first
    add(1, 2);

    // These should all satisfy Numeric
    ASSERT_TRUE(Numeric<int>);
    ASSERT_TRUE(Numeric<double>);
    ASSERT_TRUE(Numeric<float>);
    ASSERT_TRUE(Numeric<char>);
    ASSERT_TRUE(Numeric<long>);
}

TEST(runner, "Numeric concept rejects non-arithmetic types") {
    // Gate: add must work first
    add(1, 2);

    // These should NOT satisfy Numeric
    ASSERT_FALSE(Numeric<std::string>);

    struct Foo {};
    ASSERT_FALSE(Numeric<Foo>);
}

// NOTE: The following should NOT compile if you try it:
//   add(std::string("a"), std::string("b"));
// The Numeric concept should reject std::string.
// We test this via a comment rather than a runtime test -- attempting
// to call add<std::string> should produce a clear constraint error.

TESTKIT_MAIN(runner)
