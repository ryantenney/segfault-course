// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

#include <string>

static testkit::TestRunner runner("01-04-ex07: Dangling View");

TEST(runner, "make_label returns a valid owned string") {
    // make_label should return std::string — safe and owned by the caller.
    std::string result = make_label("item", 42);
    ASSERT_EQ(result, std::string("item-42"));

    std::string result2 = make_label("task", 7);
    ASSERT_EQ(result2, std::string("task-7"));
}

TEST(runner, "first_word extracts the first word") {
    std::string_view word = first_word("hello beautiful world");
    ASSERT_EQ(word, std::string_view("hello"));
}

TEST(runner, "first_word returns full string if no space") {
    std::string_view word = first_word("hello");
    ASSERT_EQ(word, std::string_view("hello"));
}

TEST(runner, "first_word handles empty string") {
    std::string_view word = first_word("");
    ASSERT_EQ(word, std::string_view(""));
}

TEST(runner, "trim_prefix returns a valid sub-view") {
    std::string data = "prefix:content";
    auto result = trim_prefix(data, 7);
    ASSERT_EQ(result, std::string_view("content"));
}

TEST(runner, "trim_prefix returns empty for n >= size") {
    std::string data = "short";
    auto result = trim_prefix(data, 100);
    ASSERT_TRUE(result.empty());
}

TESTKIT_MAIN(runner)
