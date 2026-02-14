// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <cmath>
#include <memory>
#include <string>

#include "ex03.h"

static testkit::TestRunner runner("03-27-ex03: Abstract Interface");

static bool approx_eq(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

TEST(runner, "Circle area with radius 1") {
    Circle c(1.0);
    ASSERT_TRUE(approx_eq(c.area(), M_PI));
}

TEST(runner, "Circle area with radius 5") {
    Circle c(5.0);
    ASSERT_TRUE(approx_eq(c.area(), M_PI * 25.0));
}

TEST(runner, "Circle name is Circle") {
    Circle c(1.0);
    ASSERT_EQ(c.name(), std::string("Circle"));
}

TEST(runner, "Rectangle area") {
    Rectangle r(3.0, 4.0);
    ASSERT_TRUE(approx_eq(r.area(), 12.0));
}

TEST(runner, "Rectangle name is Rectangle") {
    Rectangle r(1.0, 1.0);
    ASSERT_EQ(r.name(), std::string("Rectangle"));
}

TEST(runner, "make_circle returns a Shape that behaves as Circle") {
    std::unique_ptr<Shape> s = make_circle(2.0);
    ASSERT_EQ(s->name(), std::string("Circle"));
    ASSERT_TRUE(approx_eq(s->area(), M_PI * 4.0));
}

TEST(runner, "make_rectangle returns a Shape that behaves as Rectangle") {
    std::unique_ptr<Shape> s = make_rectangle(6.0, 7.0);
    ASSERT_EQ(s->name(), std::string("Rectangle"));
    ASSERT_TRUE(approx_eq(s->area(), 42.0));
}

TEST(runner, "polymorphism: different shapes through same interface") {
    std::unique_ptr<Shape> shapes[2];
    shapes[0] = make_circle(1.0);
    shapes[1] = make_rectangle(2.0, 3.0);

    ASSERT_EQ(shapes[0]->name(), std::string("Circle"));
    ASSERT_EQ(shapes[1]->name(), std::string("Rectangle"));
    ASSERT_TRUE(approx_eq(shapes[0]->area(), M_PI));
    ASSERT_TRUE(approx_eq(shapes[1]->area(), 6.0));
}

TESTKIT_MAIN(runner)
