// Exercise 05 — Tests (read-only)
//
// Verifies default constructor control with = default and = delete.

#include <testkit/testkit.h>
#include <type_traits>
#include <utility>
#include "ex05.h"

static testkit::TestRunner runner("03-25-ex05: Default Constructor Control");

TEST(runner, "Timestamp is default constructible") {
    // Gate: ensure getters work
    Timestamp t(1, 2);
    t.seconds();

    ASSERT_TRUE(std::is_default_constructible_v<Timestamp>);
}

TEST(runner, "default Timestamp is epoch (0, 0)") {
    Timestamp t = make_epoch();
    ASSERT_EQ(t.seconds(), 0);
    ASSERT_EQ(t.nanoseconds(), 0);
}

TEST(runner, "parameterized Timestamp works") {
    Timestamp t = make_timestamp(100, 500);
    ASSERT_EQ(t.seconds(), 100);
    ASSERT_EQ(t.nanoseconds(), 500);
}

TEST(runner, "NonDefaultable is NOT default constructible") {
    NonDefaultable nd(42);
    nd.value();  // gate

    ASSERT_TRUE((!std::is_default_constructible_v<NonDefaultable>));
}

TEST(runner, "NonDefaultable can be explicitly constructed") {
    NonDefaultable nd(99);
    ASSERT_EQ(nd.value(), 99);
}

TEST(runner, "make_pair returns two NonDefaultable objects") {
    auto [a, b] = make_pair(10, 20);
    ASSERT_EQ(a.value(), 10);
    ASSERT_EQ(b.value(), 20);
}

TESTKIT_MAIN(runner)
