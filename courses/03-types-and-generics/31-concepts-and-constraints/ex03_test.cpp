// Exercise 03 -- Tests (read-only)
//
// Verifies requires clauses on function templates.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("03-31-ex03: Requires Clause on Function");

TEST(runner, "absolute_value of positive int") {
    ASSERT_EQ(absolute_value(5), 5);
}

TEST(runner, "absolute_value of negative int") {
    ASSERT_EQ(absolute_value(-7), 7);
}

TEST(runner, "absolute_value of zero") {
    ASSERT_EQ(absolute_value(0), 0);
}

TEST(runner, "absolute_value works with double") {
    double result = absolute_value(-3.14);
    ASSERT_TRUE(result > 3.13 && result < 3.15);
}

TEST(runner, "clamp_value returns val when in range") {
    ASSERT_EQ(clamp_value(5, 0, 10), 5);
}

TEST(runner, "clamp_value returns lo when val < lo") {
    ASSERT_EQ(clamp_value(-3, 0, 10), 0);
}

TEST(runner, "clamp_value returns hi when val > hi") {
    ASSERT_EQ(clamp_value(15, 0, 10), 10);
}

TEST(runner, "clamp_value works at boundaries") {
    ASSERT_EQ(clamp_value(0, 0, 10), 0);
    ASSERT_EQ(clamp_value(10, 0, 10), 10);
}

TEST(runner, "clamp_value works with double") {
    double result = clamp_value(5.5, 1.0, 3.0);
    ASSERT_TRUE(result == 3.0);
}

TEST(runner, "clamp_value works with string") {
    std::string result = clamp_value(
        std::string("dog"),
        std::string("cat"),
        std::string("fox")
    );
    ASSERT_EQ(result, std::string("dog"));
}

// NOTE: The following should NOT compile if attempted:
//   absolute_value(5u);  // unsigned int -- not signed
// The requires clause should reject unsigned types.

TESTKIT_MAIN(runner)
