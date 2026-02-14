// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("02-16-ex03: Erase While Iterating");

TEST(runner, "remove_negative_values removes negatives") {
    std::map<std::string, int> m = {{"a", 5}, {"b", -3}, {"c", 10}, {"d", -1}};
    int removed = remove_negative_values(m);
    ASSERT_EQ(removed, 2);
    ASSERT_EQ(m.size(), 2u);
    ASSERT_TRUE(m.count("a") == 1);
    ASSERT_TRUE(m.count("c") == 1);
}

TEST(runner, "remove_negative_values with no negatives") {
    std::map<std::string, int> m = {{"x", 1}, {"y", 2}};
    int removed = remove_negative_values(m);
    ASSERT_EQ(removed, 0);
    ASSERT_EQ(m.size(), 2u);
}

TEST(runner, "remove_negative_values on empty map") {
    std::map<std::string, int> m;
    int removed = remove_negative_values(m);
    ASSERT_EQ(removed, 0);
    ASSERT_TRUE(m.empty());
}

TEST(runner, "remove_long_keys removes keys exceeding max_len") {
    std::map<std::string, int> m = {{"ab", 1}, {"abcde", 2}, {"abc", 3}, {"abcdef", 4}};
    int removed = remove_long_keys(m, 3);
    ASSERT_EQ(removed, 2);
    ASSERT_EQ(m.size(), 2u);
    ASSERT_TRUE(m.count("ab") == 1);
    ASSERT_TRUE(m.count("abc") == 1);
}

TEST(runner, "remove_long_keys keeps all when none exceed") {
    std::map<std::string, int> m = {{"a", 1}, {"bb", 2}};
    int removed = remove_long_keys(m, 5);
    ASSERT_EQ(removed, 0);
    ASSERT_EQ(m.size(), 2u);
}

TEST(runner, "remove_if_map removes matching entries") {
    std::map<std::string, int> m = {{"a", 10}, {"b", 20}, {"c", 30}};
    int removed = remove_if_map(m, [](const std::string&, int v) {
        return v >= 20;
    });
    ASSERT_EQ(removed, 2);
    ASSERT_EQ(m.size(), 1u);
    ASSERT_TRUE(m.count("a") == 1);
}

TEST(runner, "remove_if_map can filter on key and value") {
    std::map<std::string, int> m = {{"keep", 100}, {"drop", 200}, {"also_keep", 50}};
    int removed = remove_if_map(m, [](const std::string& k, int v) {
        return k == "drop" || v < 60;
    });
    ASSERT_EQ(removed, 2);
    ASSERT_EQ(m.size(), 1u);
    ASSERT_TRUE(m.count("keep") == 1);
}

TESTKIT_MAIN(runner)
