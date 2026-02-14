// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

#include <cmath>

static testkit::TestRunner runner("01-07-ex03: Unpack a struct");

TEST(runner, "make_point creates a point") {
    auto [x, y] = make_point(3.0, 4.0);
    ASSERT_EQ(x, 3.0);
    ASSERT_EQ(y, 4.0);
}

TEST(runner, "distance_from_origin computes correctly") {
    // 3-4-5 triangle
    ASSERT_EQ(distance_from_origin(make_point(3.0, 4.0)), 5.0);
    ASSERT_EQ(distance_from_origin(make_point(0.0, 0.0)), 0.0);
}

TEST(runner, "make_rect creates a rectangle") {
    auto [x, y, w, h] = make_rect(1.0, 2.0, 10.0, 5.0);
    ASSERT_EQ(x, 1.0);
    ASSERT_EQ(y, 2.0);
    ASSERT_EQ(w, 10.0);
    ASSERT_EQ(h, 5.0);
}

TEST(runner, "rect_area computes width * height") {
    ASSERT_EQ(rect_area(make_rect(0, 0, 3.0, 4.0)), 12.0);
    ASSERT_EQ(rect_area(make_rect(0, 0, 0.0, 5.0)), 0.0);
}

TEST(runner, "make_person creates a person") {
    auto [name, age] = make_person("Alice", 30);
    ASSERT_EQ(name, "Alice");
    ASSERT_EQ(age, 30);
}

TEST(runner, "greet formats correctly") {
    ASSERT_EQ(greet(make_person("Alice", 30)), "Hello, Alice (age 30)!");
    ASSERT_EQ(greet(make_person("Bob", 25)), "Hello, Bob (age 25)!");
}

TESTKIT_MAIN(runner)
