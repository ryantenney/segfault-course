// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

// Defined in ex05_helper.cpp (a second translation unit).
extern int compute_volume(int side);

static testkit::TestRunner runner("01-01-ex05: Inline Functions");

TEST(runner, "square returns x * x") {
    ASSERT_EQ(square(3), 9);
    ASSERT_EQ(square(0), 0);
    ASSERT_EQ(square(-4), 16);
}

TEST(runner, "cube returns x * x * x") {
    ASSERT_EQ(cube(2), 8);
    ASSERT_EQ(cube(3), 27);
    ASSERT_EQ(cube(-2), -8);
}

TEST(runner, "compute_volume uses cube from a second TU") {
    ASSERT_EQ(compute_volume(3), 27);
    ASSERT_EQ(compute_volume(1), 1);
}

TESTKIT_MAIN(runner)
