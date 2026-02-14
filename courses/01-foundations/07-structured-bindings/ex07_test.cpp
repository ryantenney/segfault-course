// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-07-ex07: Multi-return function (Capstone)");

TEST(runner, "analyze_text counts words") {
    auto [words, chars, longest, first] = analyze_text("hello world");
    ASSERT_EQ(words, 2);
}

TEST(runner, "analyze_text counts characters") {
    auto [words, chars, longest, first] = analyze_text("hello world");
    ASSERT_EQ(chars, 11);
}

TEST(runner, "analyze_text finds longest word") {
    auto [words, chars, longest, first] = analyze_text("I am learning cpp");
    ASSERT_EQ(longest, 8);  // "learning"
}

TEST(runner, "analyze_text captures first char") {
    auto [words, chars, longest, first] = analyze_text("hello");
    ASSERT_EQ(first, 'h');
}

TEST(runner, "analyze_text handles single word") {
    auto [words, chars, longest, first] = analyze_text("test");
    ASSERT_EQ(words, 1);
    ASSERT_EQ(chars, 4);
    ASSERT_EQ(longest, 4);
    ASSERT_EQ(first, 't');
}

TEST(runner, "analyze_text handles empty string") {
    auto [words, chars, longest, first] = analyze_text("");
    ASSERT_EQ(words, 0);
    ASSERT_EQ(chars, 0);
    ASSERT_EQ(longest, 0);
    ASSERT_EQ(first, '\0');
}

TEST(runner, "analyze_text handles multiple words") {
    auto [words, chars, longest, first] = analyze_text("the quick brown fox");
    ASSERT_EQ(words, 4);
    ASSERT_EQ(chars, 19);
    ASSERT_EQ(longest, 5);  // "quick" or "brown"
    ASSERT_EQ(first, 't');
}

TEST(runner, "text_summary formats correctly") {
    ASSERT_EQ(text_summary("hello world"), "2 words, 11 chars, longest: 5");
}

TEST(runner, "text_summary for single word") {
    ASSERT_EQ(text_summary("test"), "1 words, 4 chars, longest: 4");
}

TEST(runner, "text_summary for empty string") {
    ASSERT_EQ(text_summary(""), "0 words, 0 chars, longest: 0");
}

TESTKIT_MAIN(runner)
