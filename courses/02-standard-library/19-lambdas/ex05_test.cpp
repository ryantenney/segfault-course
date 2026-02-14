// Exercise 05 -- Tests (read-only)

#include <cmath>
#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("02-19-ex05: Generic Lambda");

TEST(runner, "make_int_adder adds integers") {
    auto adder = make_int_adder();
    ASSERT_EQ(adder(3, 4), 7);
    ASSERT_EQ(adder(-1, 1), 0);
    ASSERT_EQ(adder(0, 0), 0);
}

TEST(runner, "make_double_adder adds doubles") {
    auto adder = make_double_adder();
    // Use a tolerance check via ASSERT_TRUE
    ASSERT_TRUE(std::abs(adder(1.5, 2.5) - 4.0) < 0.001);
    ASSERT_TRUE(std::abs(adder(-1.0, 1.0) - 0.0) < 0.001);
}

TEST(runner, "apply_twice with increment lambda") {
    auto result = apply_twice(5, [](int x) { return x + 1; });
    ASSERT_EQ(result, 7);
}

TEST(runner, "apply_twice with doubling lambda") {
    auto result = apply_twice(3, [](int x) { return x * 2; });
    // 3 -> 6 -> 12
    ASSERT_EQ(result, 12);
}

TEST(runner, "apply_twice with string lambda") {
    auto result = apply_twice(std::string("ha"),
        [](const std::string& s) { return s + s; });
    // "ha" -> "haha" -> "hahahaha"
    ASSERT_EQ(result, std::string("hahahaha"));
}

TEST(runner, "make_max_finder returns maximum element") {
    auto finder = make_max_finder();
    ASSERT_EQ(finder({3, 7, 1, 9, 4}), 9);
}

TEST(runner, "make_max_finder with single element") {
    auto finder = make_max_finder();
    ASSERT_EQ(finder({42}), 42);
}

TEST(runner, "make_max_finder with negative numbers") {
    auto finder = make_max_finder();
    ASSERT_EQ(finder({-5, -1, -10}), -1);
}

TESTKIT_MAIN(runner)
