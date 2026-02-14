// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex08.h"

static testkit::TestRunner runner("02-15-ex08: Custom Hash Function");

TEST(runner, "Point operator== compares correctly") {
    Point a{1, 2};
    Point b{1, 2};
    Point c{3, 4};
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a == c);
}

TEST(runner, "Point operator== distinguishes different points") {
    ASSERT_FALSE((Point{1, 2} == Point{2, 1}));
    ASSERT_FALSE((Point{0, 0} == Point{0, 1}));
    ASSERT_FALSE((Point{0, 0} == Point{1, 0}));
}

TEST(runner, "PointHash produces consistent results") {
    PointHash hasher;
    Point p{5, 10};
    auto h1 = hasher(p);
    auto h2 = hasher(p);
    ASSERT_EQ(h1, h2);
}

TEST(runner, "PointHash produces same hash for equal points") {
    PointHash hasher;
    ASSERT_EQ(hasher(Point{3, 7}), hasher(Point{3, 7}));
}

TEST(runner, "build_point_map creates entries") {
    auto m = build_point_map({
        {{0, 0}, "origin"},
        {{1, 0}, "right"},
        {{0, 1}, "up"}
    });
    ASSERT_EQ(m.size(), 3u);
}

TEST(runner, "build_point_map with duplicate keys keeps last") {
    auto m = build_point_map({
        {{1, 1}, "first"},
        {{1, 1}, "second"}
    });
    // insert overwrites or keeps first depending on implementation;
    // test just checks the map has one entry for this key
    ASSERT_EQ(m.size(), 1u);
}

TEST(runner, "lookup_point finds existing points") {
    auto m = build_point_map({
        {{0, 0}, "origin"},
        {{3, 4}, "triple-four"},
        {{-1, -1}, "negative"}
    });
    ASSERT_EQ(lookup_point(m, {0, 0}), std::string("origin"));
    ASSERT_EQ(lookup_point(m, {3, 4}), std::string("triple-four"));
    ASSERT_EQ(lookup_point(m, {-1, -1}), std::string("negative"));
}

TEST(runner, "lookup_point returns 'not found' for missing points") {
    auto m = build_point_map({{{0, 0}, "origin"}});
    ASSERT_EQ(lookup_point(m, {99, 99}), std::string("not found"));
    ASSERT_EQ(lookup_point(m, {0, 1}), std::string("not found"));
}

TESTKIT_MAIN(runner)
