// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("02-15-ex06: Custom Comparator");

TEST(runner, "CaseInsensitiveLess orders strings case-insensitively") {
    CaseInsensitiveLess cmp;
    // "apple" < "Banana" because 'a' < 'b'
    ASSERT_TRUE(cmp("apple", "Banana"));
    ASSERT_FALSE(cmp("Banana", "apple"));
}

TEST(runner, "CaseInsensitiveLess treats same-case-different as equal") {
    CaseInsensitiveLess cmp;
    // Neither "Hello" < "hello" nor "hello" < "Hello"
    ASSERT_FALSE(cmp("Hello", "hello"));
    ASSERT_FALSE(cmp("hello", "Hello"));
}

TEST(runner, "build_case_insensitive_map creates entries") {
    auto m = build_case_insensitive_map({
        {"Host", 1}, {"Port", 2}, {"Mode", 3}
    });
    ASSERT_EQ(m.size(), 3u);
}

TEST(runner, "build_case_insensitive_map merges case-insensitive duplicates") {
    auto m = build_case_insensitive_map({
        {"host", 1}, {"HOST", 2}, {"Host", 3}
    });
    // All three are the same key case-insensitively; last value wins
    ASSERT_EQ(m.size(), 1u);
    // The value should be the last one inserted
    ASSERT_EQ(m.begin()->second, 3);
}

TEST(runner, "lookup_case_insensitive finds keys regardless of case") {
    auto m = build_case_insensitive_map({
        {"Hello", 42}, {"World", 99}
    });
    ASSERT_EQ(lookup_case_insensitive(m, "hello"), 42);
    ASSERT_EQ(lookup_case_insensitive(m, "HELLO"), 42);
    ASSERT_EQ(lookup_case_insensitive(m, "Hello"), 42);
    ASSERT_EQ(lookup_case_insensitive(m, "world"), 99);
    ASSERT_EQ(lookup_case_insensitive(m, "WORLD"), 99);
}

TEST(runner, "lookup_case_insensitive returns -1 for missing keys") {
    auto m = build_case_insensitive_map({{"Key", 10}});
    ASSERT_EQ(lookup_case_insensitive(m, "missing"), -1);
}

TEST(runner, "case-insensitive map iterates in case-insensitive sorted order") {
    auto m = build_case_insensitive_map({
        {"Cherry", 3}, {"apple", 1}, {"BANANA", 2}
    });
    // Should iterate: apple, BANANA, Cherry (case-insensitive sort)
    auto it = m.begin();
    ASSERT_EQ(it->second, 1);  // apple
    ++it;
    ASSERT_EQ(it->second, 2);  // BANANA
    ++it;
    ASSERT_EQ(it->second, 3);  // Cherry
}

TESTKIT_MAIN(runner)
