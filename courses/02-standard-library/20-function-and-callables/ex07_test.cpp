// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex07.h"

#include <vector>

static testkit::TestRunner runner("02-20-ex07: Higher-Order Function");

TEST(runner, "make_multiplier creates a multiplier function") {
    auto times3 = make_multiplier(3);
    ASSERT_EQ(times3(5), 15);
    ASSERT_EQ(times3(0), 0);
    ASSERT_EQ(times3(-2), -6);
}

TEST(runner, "make_multiplier with factor 1 is identity") {
    auto times1 = make_multiplier(1);
    ASSERT_EQ(times1(42), 42);
    ASSERT_EQ(times1(-7), -7);
}

TEST(runner, "compose applies g then f") {
    auto double_it = [](int x) { return x * 2; };
    auto add_one = [](int x) { return x + 1; };
    // compose(double_it, add_one)(5) = double_it(add_one(5)) = double_it(6) = 12
    auto composed = compose(double_it, add_one);
    ASSERT_EQ(composed(5), 12);
}

TEST(runner, "compose order matters") {
    auto double_it = [](int x) { return x * 2; };
    auto add_one = [](int x) { return x + 1; };
    // compose(add_one, double_it)(5) = add_one(double_it(5)) = add_one(10) = 11
    auto composed = compose(add_one, double_it);
    ASSERT_EQ(composed(5), 11);
}

TEST(runner, "compose with identity") {
    auto identity = [](int x) { return x; };
    auto add_ten = [](int x) { return x + 10; };
    auto composed = compose(identity, add_ten);
    ASSERT_EQ(composed(7), 17);
}

TEST(runner, "call_n_times invokes f n times") {
    auto square = [](int x) { return x * x; };
    auto repeater = call_n_times(square, 3);
    auto results = repeater(4);
    ASSERT_EQ(results.size(), 3u);
    ASSERT_EQ(results[0], 16);
    ASSERT_EQ(results[1], 16);
    ASSERT_EQ(results[2], 16);
}

TEST(runner, "call_n_times with n=0 returns empty vector") {
    auto fn = [](int x) { return x; };
    auto repeater = call_n_times(fn, 0);
    auto results = repeater(99);
    ASSERT_EQ(results.size(), 0u);
}

TEST(runner, "call_n_times with stateful callable invokes fresh each time") {
    int counter = 0;
    auto counting = [&counter](int x) { return x + (++counter); };
    auto repeater = call_n_times(counting, 3);
    auto results = repeater(10);
    ASSERT_EQ(results.size(), 3u);
    // counter increments each call: 10+1, 10+2, 10+3
    ASSERT_EQ(results[0], 11);
    ASSERT_EQ(results[1], 12);
    ASSERT_EQ(results[2], 13);
}

TESTKIT_MAIN(runner)
