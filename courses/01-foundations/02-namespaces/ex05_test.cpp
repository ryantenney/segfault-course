// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

// This file has its own bonus() in an anonymous namespace.
// It must not conflict with the bonus() in ex05_detail.cpp.
namespace {

int bonus() {
    return 5;
}

} // anonymous namespace

namespace scoring {

int compute_score_a(int base) {
    return base + bonus();
}

} // namespace scoring

static testkit::TestRunner runner("01-02-ex05: Anonymous Namespace");

TEST(runner, "compute_score_a uses this file's bonus (5)") {
    ASSERT_EQ(scoring::compute_score_a(100), 105);
    ASSERT_EQ(scoring::compute_score_a(0), 5);
}

TEST(runner, "compute_score_b uses ex05_detail's bonus (10)") {
    ASSERT_EQ(scoring::compute_score_b(100), 110);
    ASSERT_EQ(scoring::compute_score_b(0), 10);
}

TEST(runner, "the two bonus functions return different values") {
    ASSERT_NE(scoring::compute_score_a(0), scoring::compute_score_b(0));
}

TESTKIT_MAIN(runner)
