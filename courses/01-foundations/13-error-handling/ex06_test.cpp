// Exercise 06 — Tests (read-only)

#include <type_traits>
#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-13-ex06: noexcept Correctness");

TEST(runner, "add returns the sum") {
    ASSERT_EQ(add(3, 4), 7);
    ASSERT_EQ(add(-1, 1), 0);
    ASSERT_EQ(add(0, 0), 0);
}

TEST(runner, "add is noexcept") {
    add(0, 0); // gates on TODO()
    ASSERT_TRUE(noexcept(add(1, 2)));
}

TEST(runner, "safe_access returns element at valid index") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(safe_access(v, 0, -1), 10);
    ASSERT_EQ(safe_access(v, 2, -1), 30);
}

TEST(runner, "safe_access returns default for invalid index") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(safe_access(v, 5, -1), -1);
    ASSERT_EQ(safe_access(v, 100, 42), 42);
}

TEST(runner, "safe_access is noexcept") {
    std::vector<int> v = {1};
    safe_access(v, 0, 0); // gates on TODO()
    ASSERT_TRUE(noexcept(safe_access(v, 0, 0)));
}

TEST(runner, "checked_access returns element at valid index") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(checked_access(v, 1), 20);
}

TEST(runner, "checked_access throws for invalid index") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_THROWS(checked_access(v, 5), std::out_of_range);
}

TEST(runner, "checked_access is NOT noexcept") {
    std::vector<int> v = {1};
    ASSERT_FALSE(noexcept(checked_access(v, 0)));
}

TEST(runner, "swap_values swaps two integers") {
    int a = 10, b = 20;
    swap_values(a, b);
    ASSERT_EQ(a, 20);
    ASSERT_EQ(b, 10);
}

TEST(runner, "swap_values is noexcept") {
    int a = 1, b = 2;
    swap_values(a, b); // gates on TODO()
    ASSERT_TRUE(noexcept(swap_values(a, b)));
}

TESTKIT_MAIN(runner)
