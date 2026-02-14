// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-03-ex01: Prove Value Semantics");

TEST(runner, "make_point creates a point with given coordinates") {
    Point p = make_point(3, 4);
    ASSERT_EQ(p.x, 3);
    ASSERT_EQ(p.y, 4);
}

TEST(runner, "offset_point returns a modified copy") {
    Point p = make_point(1, 2);
    Point q = offset_point(p, 10, 20);
    ASSERT_EQ(q.x, 11);
    ASSERT_EQ(q.y, 22);
}

TEST(runner, "original is unchanged after offset_point") {
    Point p = make_point(5, 7);
    Point q = offset_point(p, 100, 200);
    // p must be unchanged — value semantics means the function got a copy
    ASSERT_EQ(p.x, 5);
    ASSERT_EQ(p.y, 7);
    // q has the new values
    ASSERT_EQ(q.x, 105);
    ASSERT_EQ(q.y, 207);
}

TEST(runner, "assignment creates an independent copy") {
    Point p = make_point(1, 2);
    Point q = p;        // copy
    q.x = 999;          // modify the copy
    ASSERT_EQ(p.x, 1);  // original is unchanged
    ASSERT_EQ(q.x, 999);
}

TESTKIT_MAIN(runner)
