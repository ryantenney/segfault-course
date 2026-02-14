// Exercise 05 -- Tests (read-only)
//
// Verifies concept-based overloading.

#include <testkit/testkit.h>
#include <string>
#include "ex05.h"

static testkit::TestRunner runner("03-31-ex05: Concept-Based Overloading");

TEST(runner, "describe int returns integer prefix") {
    std::string result = describe(42);
    ASSERT_EQ(result, std::string("integer: 42"));
}

TEST(runner, "describe long returns integer prefix") {
    std::string result = describe(100L);
    ASSERT_EQ(result, std::string("integer: 100"));
}

TEST(runner, "describe double returns float prefix") {
    std::string result = describe(3.14);
    ASSERT_TRUE(result.substr(0, 7) == "float: ");
    ASSERT_TRUE(result.find("3.14") != std::string::npos);
}

TEST(runner, "describe float returns float prefix") {
    std::string result = describe(2.5f);
    ASSERT_TRUE(result.substr(0, 7) == "float: ");
    ASSERT_TRUE(result.find("2.5") != std::string::npos);
}

TEST(runner, "double_it with int") {
    ASSERT_EQ(double_it(5), 10);
}

TEST(runner, "double_it with double") {
    double result = double_it(3.5);
    ASSERT_TRUE(result == 7.0);
}

TEST(runner, "double_it with long") {
    ASSERT_EQ(double_it(100L), 200L);
}

TEST(runner, "concepts are correctly defined") {
    // Gate: describe must work first
    describe(1);

    ASSERT_TRUE(Integral<int>);
    ASSERT_TRUE(Integral<long>);
    ASSERT_TRUE(Integral<char>);
    ASSERT_FALSE(Integral<double>);
    ASSERT_FALSE(Integral<float>);

    ASSERT_TRUE(FloatingPoint<double>);
    ASSERT_TRUE(FloatingPoint<float>);
    ASSERT_FALSE(FloatingPoint<int>);
}

TESTKIT_MAIN(runner)
