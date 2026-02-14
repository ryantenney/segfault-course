// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("02-15-ex04: try_emplace for Lazy Init");

TEST(runner, "get_or_create inserts default when key is missing") {
    std::unordered_map<std::string, std::string> m;
    auto& val = get_or_create(m, "color", "blue");
    ASSERT_EQ(val, std::string("blue"));
    ASSERT_EQ(m.size(), 1u);
}

TEST(runner, "get_or_create returns existing value without overwriting") {
    std::unordered_map<std::string, std::string> m = {{"color", "red"}};
    auto& val = get_or_create(m, "color", "blue");
    ASSERT_EQ(val, std::string("red"));  // not overwritten
    ASSERT_EQ(m.size(), 1u);
}

TEST(runner, "get_or_create returns a mutable reference") {
    std::unordered_map<std::string, std::string> m;
    auto& val = get_or_create(m, "name", "default");
    val = "updated";
    ASSERT_EQ(m.at("name"), std::string("updated"));
}

TEST(runner, "group_by_length groups words correctly") {
    auto groups = group_by_length({"hi", "hey", "go", "cat", "a", "dog"});

    ASSERT_EQ(groups.at(1).size(), 1u);
    ASSERT_EQ(groups.at(1)[0], std::string("a"));

    ASSERT_EQ(groups.at(2).size(), 2u);
    ASSERT_EQ(groups.at(2)[0], std::string("hi"));
    ASSERT_EQ(groups.at(2)[1], std::string("go"));

    ASSERT_EQ(groups.at(3).size(), 3u);
    ASSERT_EQ(groups.at(3)[0], std::string("hey"));
    ASSERT_EQ(groups.at(3)[1], std::string("cat"));
    ASSERT_EQ(groups.at(3)[2], std::string("dog"));
}

TEST(runner, "group_by_length with empty input returns empty map") {
    auto groups = group_by_length({});
    ASSERT_EQ(groups.size(), 0u);
}

TEST(runner, "group_by_length preserves insertion order within groups") {
    auto groups = group_by_length({"alpha", "bravo", "delta"});
    // All length-5
    ASSERT_EQ(groups.at(5).size(), 3u);
    ASSERT_EQ(groups.at(5)[0], std::string("alpha"));
    ASSERT_EQ(groups.at(5)[1], std::string("bravo"));
    ASSERT_EQ(groups.at(5)[2], std::string("delta"));
}

TESTKIT_MAIN(runner)
