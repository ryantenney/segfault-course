// Exercise 06 -- Tests (read-only)
//
// Verifies usage of standard library concepts from <concepts>.

#include <testkit/testkit.h>
#include <string>
#include "ex06.h"

static testkit::TestRunner runner("03-31-ex06: Standard Library Concepts");

TEST(runner, "to_int converts char to int") {
    int result = to_int('A');
    ASSERT_EQ(result, 65);
}

TEST(runner, "to_int converts long to int") {
    int result = to_int(42L);
    ASSERT_EQ(result, 42);
}

TEST(runner, "to_int converts short to int") {
    int result = to_int(static_cast<short>(7));
    ASSERT_EQ(result, 7);
}

TEST(runner, "halve divides double by two") {
    double result = halve(10.0);
    ASSERT_TRUE(result == 5.0);
}

TEST(runner, "halve divides float by two") {
    float result = halve(7.0f);
    ASSERT_TRUE(result == 3.5f);
}

TEST(runner, "stringify converts std::string") {
    std::string result = stringify(std::string("hello"));
    ASSERT_EQ(result, std::string("hello"));
}

TEST(runner, "stringify converts another string") {
    std::string result = stringify(std::string("world"));
    ASSERT_EQ(result, std::string("world"));
}

TEST(runner, "are_equal with equal ints") {
    ASSERT_TRUE(are_equal(5, 5));
}

TEST(runner, "are_equal with unequal ints") {
    ASSERT_FALSE(are_equal(5, 10));
}

TEST(runner, "are_equal with strings") {
    ASSERT_TRUE(are_equal(std::string("abc"), std::string("abc")));
    ASSERT_FALSE(are_equal(std::string("abc"), std::string("xyz")));
}

// NOTE: The following should NOT compile:
//   to_int(3.14);        // double is not std::integral
//   halve(5);            // int is not std::floating_point

TESTKIT_MAIN(runner)
