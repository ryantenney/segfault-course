// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-07-ex05: Binding with const/reference");

TEST(runner, "swap_values exchanges two entries") {
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    swap_values(m, "a", "b");
    ASSERT_EQ(m["a"], 2);
    ASSERT_EQ(m["b"], 1);
}

TEST(runner, "swap_values does nothing if key is missing") {
    std::map<std::string, int> m = {{"a", 1}};
    swap_values(m, "a", "z");
    ASSERT_EQ(m["a"], 1);
    ASSERT_EQ(m.count("z"), 0u);
}

TEST(runner, "increment_all adds amount to every value") {
    std::map<std::string, int> m = {{"x", 10}, {"y", 20}};
    increment_all(m, 5);
    ASSERT_EQ(m["x"], 15);
    ASSERT_EQ(m["y"], 25);
}

TEST(runner, "increment_all with negative amount") {
    std::map<std::string, int> m = {{"a", 100}};
    increment_all(m, -30);
    ASSERT_EQ(m["a"], 70);
}

TEST(runner, "summarize formats map entries") {
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    ASSERT_EQ(summarize(m), "a:1 b:2");
}

TEST(runner, "summarize handles single entry") {
    std::map<std::string, int> m = {{"only", 42}};
    ASSERT_EQ(summarize(m), "only:42");
}

TEST(runner, "summarize handles empty map") {
    std::map<std::string, int> m;
    ASSERT_EQ(summarize(m), std::string(""));
}

TEST(runner, "any_exceeds returns true when value exceeds threshold") {
    std::map<std::string, int> m = {{"a", 5}, {"b", 15}, {"c", 10}};
    ASSERT_TRUE(any_exceeds(m, 12));
}

TEST(runner, "any_exceeds returns false when no value exceeds threshold") {
    std::map<std::string, int> m = {{"a", 5}, {"b", 10}};
    ASSERT_FALSE(any_exceeds(m, 10));
}

TEST(runner, "any_exceeds returns false for empty map") {
    std::map<std::string, int> m;
    ASSERT_FALSE(any_exceeds(m, 0));
}

TESTKIT_MAIN(runner)
