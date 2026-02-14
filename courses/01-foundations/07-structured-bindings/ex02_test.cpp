// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-07-ex02: Iterate a map");

TEST(runner, "get_keys returns all keys in order") {
    std::map<std::string, int> m = {{"cherry", 3}, {"apple", 1}, {"banana", 2}};
    auto keys = get_keys(m);
    ASSERT_EQ(keys.size(), 3u);
    ASSERT_EQ(keys[0], "apple");
    ASSERT_EQ(keys[1], "banana");
    ASSERT_EQ(keys[2], "cherry");
}

TEST(runner, "get_keys returns empty for empty map") {
    std::map<std::string, int> m;
    ASSERT_TRUE(get_keys(m).empty());
}

TEST(runner, "sum_values totals all values") {
    std::map<std::string, int> m = {{"a", 10}, {"b", 20}, {"c", 30}};
    ASSERT_EQ(sum_values(m), 60);
}

TEST(runner, "sum_values returns 0 for empty map") {
    std::map<std::string, int> m;
    ASSERT_EQ(sum_values(m), 0);
}

TEST(runner, "key_of_max finds the key with largest value") {
    std::map<std::string, int> m = {{"x", 5}, {"y", 15}, {"z", 10}};
    ASSERT_EQ(key_of_max(m), "y");
}

TEST(runner, "key_of_max returns empty for empty map") {
    std::map<std::string, int> m;
    ASSERT_EQ(key_of_max(m), std::string(""));
}

TEST(runner, "format_map produces key=value pairs") {
    std::map<std::string, int> m = {{"b", 2}, {"a", 1}};
    ASSERT_EQ(format_map(m), "a=1,b=2");
}

TEST(runner, "format_map handles single entry") {
    std::map<std::string, int> m = {{"only", 42}};
    ASSERT_EQ(format_map(m), "only=42");
}

TEST(runner, "format_map returns empty for empty map") {
    std::map<std::string, int> m;
    ASSERT_EQ(format_map(m), std::string(""));
}

TESTKIT_MAIN(runner)
