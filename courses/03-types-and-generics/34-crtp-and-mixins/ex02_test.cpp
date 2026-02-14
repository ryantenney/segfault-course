// Exercise 02 -- Tests (read-only)
//
// Verifies CRTP static interface dispatch for shapes.

#include <testkit/testkit.h>
#include <cmath>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("03-34-ex02: Static Interface via CRTP");

static constexpr double PI = 3.14159265358979323846;
static constexpr double EPS = 1e-6;

TEST(runner, "Circle area is pi * r^2") {
    Circle c(5.0);
    double expected = PI * 25.0;
    ASSERT_TRUE(std::abs(c.area() - expected) < EPS);
}

TEST(runner, "Circle perimeter is 2 * pi * r") {
    Circle c(3.0);
    double expected = 2.0 * PI * 3.0;
    ASSERT_TRUE(std::abs(c.perimeter() - expected) < EPS);
}

TEST(runner, "Rectangle area is width * height") {
    Rectangle r(4.0, 7.0);
    ASSERT_TRUE(std::abs(r.area() - 28.0) < EPS);
}

TEST(runner, "Rectangle perimeter is 2*(w+h)") {
    Rectangle r(4.0, 7.0);
    ASSERT_TRUE(std::abs(r.perimeter() - 22.0) < EPS);
}

TEST(runner, "Shape<Circle>::area dispatches to Circle::area_impl") {
    Circle c(1.0);
    const Shape<Circle>& s = c;
    ASSERT_TRUE(std::abs(s.area() - PI) < EPS);
}

TEST(runner, "Shape<Rectangle>::perimeter dispatches to Rectangle") {
    Rectangle r(3.0, 5.0);
    const Shape<Rectangle>& s = r;
    ASSERT_TRUE(std::abs(s.perimeter() - 16.0) < EPS);
}

TEST(runner, "print_area formats Circle correctly") {
    Circle c(5.0);
    std::string result = print_area(c);
    // Must start with "Circle: "
    ASSERT_TRUE(result.substr(0, 8) == "Circle: ");
    // The numeric part should parse to roughly pi*25
    double val = std::stod(result.substr(8));
    ASSERT_TRUE(std::abs(val - PI * 25.0) < 0.01);
}

TEST(runner, "print_area formats Rectangle correctly") {
    Rectangle r(4.0, 7.0);
    std::string result = print_area(r);
    ASSERT_TRUE(result.substr(0, 11) == "Rectangle: ");
    double val = std::stod(result.substr(11));
    ASSERT_TRUE(std::abs(val - 28.0) < 0.01);
}

TESTKIT_MAIN(runner)
