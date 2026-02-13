// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-01-ex07: Anonymous Namespaces");

TEST(runner, "compute_a returns detail() + 10") {
    ASSERT_EQ(compute_a(), 52);   // detail() = 42, + 10 = 52
}

TEST(runner, "compute_b returns detail() * 3") {
    ASSERT_EQ(compute_b(), 21);   // detail() = 7, * 3 = 21
}

TEST(runner, "compute_a and compute_b use different detail() functions") {
    // The two detail() functions return different values, proving
    // they are separate functions with internal linkage.
    ASSERT_NE(compute_a() - 10, compute_b() / 3);
}

TESTKIT_MAIN(runner)
