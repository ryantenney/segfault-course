// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex07.h"

static testkit::TestRunner runner("01-02-ex07: ADL Basics");

TEST(runner, "geometry::describe formats a circle") {
    geometry::Circle c{5.0};
    ASSERT_EQ(geometry::describe(c), std::string("circle(r=5.000000)"));
}

TEST(runner, "describe_shape uses ADL to find geometry::describe") {
    geometry::Circle c{3.0};
    std::string result = describe_shape(c);
    // Should call geometry::describe, not the global one
    ASSERT_EQ(result, std::string("circle(r=3.000000)"));
}

TEST(runner, "describe_number calls global describe for int") {
    ASSERT_EQ(describe_number(42), std::string("int(42)"));
    ASSERT_EQ(describe_number(-1), std::string("int(-1)"));
}

TESTKIT_MAIN(runner)
