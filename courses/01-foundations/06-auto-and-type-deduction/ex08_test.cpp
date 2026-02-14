// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

#include <type_traits>

static testkit::TestRunner runner("01-06-ex08: auto Return Type");

TEST(runner, "absolute returns positive values") {
    ASSERT_EQ(absolute(-5), 5);
    ASSERT_EQ(absolute(5), 5);
    ASSERT_EQ(absolute(0), 0);
}

TEST(runner, "max_of returns the larger value") {
    ASSERT_EQ(max_of(3, 7), 7);
    ASSERT_EQ(max_of(10, 2), 10);
    ASSERT_EQ(max_of(5, 5), 5);
}

TEST(runner, "is_palindrome detects palindromes") {
    ASSERT_TRUE(is_palindrome("racecar"));
    ASSERT_TRUE(is_palindrome("madam"));
    ASSERT_TRUE(is_palindrome("a"));
    ASSERT_TRUE(is_palindrome(""));
}

TEST(runner, "is_palindrome rejects non-palindromes") {
    ASSERT_FALSE(is_palindrome("hello"));
    ASSERT_FALSE(is_palindrome("ab"));
}

TEST(runner, "repeat returns n copies") {
    auto v = repeat(7, 3);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_EQ(v[0], 7);
    ASSERT_EQ(v[1], 7);
    ASSERT_EQ(v[2], 7);
}

TEST(runner, "repeat with 0 returns empty vector") {
    auto v = repeat(1, 0);
    ASSERT_TRUE(v.empty());
}

TEST(runner, "safe_get returns element when in range") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(safe_get(v, 0, -1), 10);
    ASSERT_EQ(safe_get(v, 2, -1), 30);
}

TEST(runner, "safe_get returns fallback when out of range") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(safe_get(v, 5, -1), -1);
    ASSERT_EQ(safe_get(v, -1, 99), 99);
}

TESTKIT_MAIN(runner)
