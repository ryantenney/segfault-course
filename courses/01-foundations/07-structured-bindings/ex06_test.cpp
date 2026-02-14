// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-07-ex06: If-init with binding");

TEST(runner, "describe_insert reports insertion") {
    std::map<std::string, int> m;
    ASSERT_EQ(describe_insert(m, "x", 10), "inserted: x");
}

TEST(runner, "describe_insert reports existing key") {
    std::map<std::string, int> m = {{"x", 10}};
    ASSERT_EQ(describe_insert(m, "x", 20), "exists: x");
}

TEST(runner, "describe_insert does not overwrite existing value") {
    std::map<std::string, int> m = {{"x", 10}};
    describe_insert(m, "x", 99);
    ASSERT_EQ(m["x"], 10);
}

TEST(runner, "find_or returns the value when key exists") {
    std::map<std::string, int> m = {{"a", 42}};
    ASSERT_EQ(find_or(m, "a", -1), 42);
}

TEST(runner, "find_or returns fallback when key is missing") {
    std::map<std::string, int> m = {{"a", 42}};
    ASSERT_EQ(find_or(m, "b", -1), -1);
}

TEST(runner, "classify_value returns positive") {
    std::map<std::string, int> m = {{"x", 5}};
    ASSERT_EQ(classify_value(m, "x"), "positive");
}

TEST(runner, "classify_value returns non-positive for zero") {
    std::map<std::string, int> m = {{"x", 0}};
    ASSERT_EQ(classify_value(m, "x"), "non-positive");
}

TEST(runner, "classify_value returns non-positive for negative") {
    std::map<std::string, int> m = {{"x", -3}};
    ASSERT_EQ(classify_value(m, "x"), "non-positive");
}

TEST(runner, "classify_value returns missing for absent key") {
    std::map<std::string, int> m;
    ASSERT_EQ(classify_value(m, "x"), "missing");
}

TESTKIT_MAIN(runner)
