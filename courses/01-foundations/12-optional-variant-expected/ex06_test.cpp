// Exercise 06 — Tests (read-only)

#include <cmath>
#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-12-ex06: Overloaded Visitor");

TEST(runner, "describe_shape for Circle") {
    Shape s = Circle{5.0};
    std::string desc = describe_shape(s);
    // std::to_string(5.0) produces "5.000000" on most platforms.
    ASSERT_EQ(desc, std::string("circle(r=" + std::to_string(5.0) + ")"));
}

TEST(runner, "describe_shape for Rectangle") {
    Shape s = Rectangle{3.0, 4.0};
    std::string desc = describe_shape(s);
    ASSERT_EQ(desc, std::string("rect(" + std::to_string(3.0) + "x" + std::to_string(4.0) + ")"));
}

TEST(runner, "describe_shape for Triangle") {
    Shape s = Triangle{6.0, 3.0};
    std::string desc = describe_shape(s);
    ASSERT_EQ(desc, std::string("tri(b=" + std::to_string(6.0) + ",h=" + std::to_string(3.0) + ")"));
}

// Helper to compare doubles within tolerance
static void assert_near(double actual, double expected, double epsilon = 0.001) {
    if (std::abs(actual - expected) > epsilon) {
        std::ostringstream ss;
        ss << "expected " << actual << " to be near " << expected;
        throw testkit::assertion_error(ss.str());
    }
}

TEST(runner, "shape_area for Circle") {
    Shape s = Circle{5.0};
    assert_near(shape_area(s), 3.14159265358979 * 25.0);
}

TEST(runner, "shape_area for Rectangle") {
    Shape s = Rectangle{3.0, 4.0};
    assert_near(shape_area(s), 12.0);
}

TEST(runner, "shape_area for Triangle") {
    Shape s = Triangle{6.0, 3.0};
    assert_near(shape_area(s), 9.0);
}

TEST(runner, "shape_area for unit circle") {
    Shape s = Circle{1.0};
    assert_near(shape_area(s), 3.14159265358979);
}

TESTKIT_MAIN(runner)
