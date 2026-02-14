// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("02-19-ex08: Stateful Comparator");

TEST(runner, "configurable_sort ascending") {
    auto result = configurable_sort({5, 3, 1, 4, 2}, true);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 4);
    ASSERT_EQ(result[4], 5);
}

TEST(runner, "configurable_sort descending") {
    auto result = configurable_sort({5, 3, 1, 4, 2}, false);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 5);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 2);
    ASSERT_EQ(result[4], 1);
}

TEST(runner, "configurable_sort handles single element") {
    auto result = configurable_sort({42}, true);
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 42);
}

TEST(runner, "priority_sort puts priority items first") {
    std::set<std::string> priority = {"urgent", "important"};
    auto result = priority_sort(
        {"banana", "urgent", "apple", "important", "cherry"},
        priority);
    ASSERT_EQ(result.size(), 5u);
    // priority items come first
    ASSERT_TRUE(result[0] == "urgent" || result[0] == "important");
    ASSERT_TRUE(result[1] == "urgent" || result[1] == "important");
    // remaining items are alphabetical
    ASSERT_EQ(result[2], std::string("apple"));
    ASSERT_EQ(result[3], std::string("banana"));
    ASSERT_EQ(result[4], std::string("cherry"));
}

TEST(runner, "priority_sort with no priority items") {
    std::set<std::string> priority = {"xyz"};
    auto result = priority_sort({"cherry", "apple", "banana"}, priority);
    ASSERT_EQ(result[0], std::string("apple"));
    ASSERT_EQ(result[1], std::string("banana"));
    ASSERT_EQ(result[2], std::string("cherry"));
}

TEST(runner, "priority_sort with all priority items") {
    std::set<std::string> priority = {"b", "a", "c"};
    auto result = priority_sort({"c", "a", "b"}, priority);
    // All are priority -- preserved in their original relative order
    ASSERT_EQ(result.size(), 3u);
}

TEST(runner, "nth_element_sort puts divisible elements first") {
    auto result = nth_element_sort({7, 6, 5, 4, 3, 2, 1}, 3);
    // Divisible by 3: 6, 3 -> sorted ascending: 3, 6
    // Not divisible: 7, 5, 4, 2, 1 -> sorted ascending: 1, 2, 4, 5, 7
    ASSERT_EQ(result.size(), 7u);
    ASSERT_EQ(result[0], 3);
    ASSERT_EQ(result[1], 6);
    ASSERT_EQ(result[2], 1);
    ASSERT_EQ(result[3], 2);
    ASSERT_EQ(result[4], 4);
    ASSERT_EQ(result[5], 5);
    ASSERT_EQ(result[6], 7);
}

TEST(runner, "nth_element_sort with none divisible") {
    auto result = nth_element_sort({1, 5, 7}, 3);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 5);
    ASSERT_EQ(result[2], 7);
}

TEST(runner, "nth_element_sort with all divisible") {
    auto result = nth_element_sort({9, 3, 6}, 3);
    ASSERT_EQ(result[0], 3);
    ASSERT_EQ(result[1], 6);
    ASSERT_EQ(result[2], 9);
}

TESTKIT_MAIN(runner)
