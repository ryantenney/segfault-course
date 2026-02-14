// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-11-ex08: Move in Algorithms");

TEST(runner, "bulk_move transfers all elements") {
    std::vector<std::string> src = {"alpha", "beta", "gamma"};
    std::vector<std::string> dst(3); // pre-sized destination
    bulk_move(src, dst);
    ASSERT_EQ(dst[0], std::string("alpha"));
    ASSERT_EQ(dst[1], std::string("beta"));
    ASSERT_EQ(dst[2], std::string("gamma"));
}

TEST(runner, "bulk_move leaves source elements in moved-from state") {
    std::vector<std::string> src = {"hello", "world"};
    std::vector<std::string> dst(2);
    bulk_move(src, dst);
    // Moved-from strings are typically empty
    ASSERT_TRUE(src[0].empty());
    ASSERT_TRUE(src[1].empty());
}

TEST(runner, "extract_range extracts a sub-range") {
    std::vector<std::string> src = {"a", "b", "c", "d", "e"};
    auto result = extract_range(src, 1, 4);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("b"));
    ASSERT_EQ(result[1], std::string("c"));
    ASSERT_EQ(result[2], std::string("d"));
}

TEST(runner, "extract_range leaves extracted elements moved-from") {
    std::vector<std::string> src = {"x", "y", "z"};
    auto result = extract_range(src, 0, 2);
    ASSERT_TRUE(src[0].empty());
    ASSERT_TRUE(src[1].empty());
    ASSERT_EQ(src[2], std::string("z")); // untouched
}

TEST(runner, "partition_by_length splits correctly") {
    std::vector<std::string> src = {"hi", "hello", "yo", "wonderful", "ok"};
    auto [short_strs, long_strs] = partition_by_length(src, 3);
    // short: "hi" (2), "yo" (2), "ok" (2)
    // long:  "hello" (5), "wonderful" (9)
    ASSERT_EQ(short_strs.size(), 3u);
    ASSERT_EQ(long_strs.size(), 2u);
}

TEST(runner, "partition_by_length preserves values") {
    std::vector<std::string> src = {"ab", "abcdef"};
    auto [short_strs, long_strs] = partition_by_length(src, 3);
    ASSERT_EQ(short_strs.size(), 1u);
    ASSERT_EQ(short_strs[0], std::string("ab"));
    ASSERT_EQ(long_strs.size(), 1u);
    ASSERT_EQ(long_strs[0], std::string("abcdef"));
}

TESTKIT_MAIN(runner)
