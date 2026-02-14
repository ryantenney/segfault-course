// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("02-15-ex01: Word Frequency Counter");

TEST(runner, "counts single occurrences") {
    auto counts = count_words({"apple", "banana", "cherry"});
    ASSERT_EQ(counts.size(), 3u);
    ASSERT_EQ(counts.at("apple"), 1);
    ASSERT_EQ(counts.at("banana"), 1);
    ASSERT_EQ(counts.at("cherry"), 1);
}

TEST(runner, "counts multiple occurrences") {
    auto counts = count_words({"the", "cat", "the", "dog", "the"});
    ASSERT_EQ(counts.at("the"), 3);
    ASSERT_EQ(counts.at("cat"), 1);
    ASSERT_EQ(counts.at("dog"), 1);
}

TEST(runner, "empty input returns empty map") {
    auto counts = count_words({});
    ASSERT_EQ(counts.size(), 0u);
}

TEST(runner, "all same word") {
    auto counts = count_words({"hello", "hello", "hello"});
    ASSERT_EQ(counts.size(), 1u);
    ASSERT_EQ(counts.at("hello"), 3);
}

TESTKIT_MAIN(runner)
