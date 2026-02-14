// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("02-15-ex07: Multimap");

TEST(runner, "build_tag_index creates entries") {
    auto index = build_tag_index({
        {"fruit", "apple"},
        {"fruit", "banana"},
        {"veggie", "carrot"}
    });
    ASSERT_EQ(index.size(), 3u);
    ASSERT_EQ(index.count("fruit"), 2u);
    ASSERT_EQ(index.count("veggie"), 1u);
}

TEST(runner, "items_for_tag returns all items for a tag") {
    auto index = build_tag_index({
        {"lang", "C++"},
        {"lang", "Rust"},
        {"lang", "Go"},
        {"os", "Linux"}
    });
    auto items = items_for_tag(index, "lang");
    ASSERT_EQ(items.size(), 3u);
    ASSERT_EQ(items[0], std::string("C++"));
    ASSERT_EQ(items[1], std::string("Rust"));
    ASSERT_EQ(items[2], std::string("Go"));
}

TEST(runner, "items_for_tag returns empty vector for unknown tag") {
    auto index = build_tag_index({{"fruit", "apple"}});
    auto items = items_for_tag(index, "veggie");
    ASSERT_EQ(items.size(), 0u);
}

TEST(runner, "items_for_tag with single item") {
    auto index = build_tag_index({{"os", "Linux"}});
    auto items = items_for_tag(index, "os");
    ASSERT_EQ(items.size(), 1u);
    ASSERT_EQ(items[0], std::string("Linux"));
}

TEST(runner, "all_tags returns sorted unique tags") {
    auto index = build_tag_index({
        {"c", "item1"},
        {"a", "item2"},
        {"b", "item3"},
        {"a", "item4"},
        {"c", "item5"}
    });
    auto tags = all_tags(index);
    ASSERT_EQ(tags.size(), 3u);
    ASSERT_EQ(tags[0], std::string("a"));
    ASSERT_EQ(tags[1], std::string("b"));
    ASSERT_EQ(tags[2], std::string("c"));
}

TEST(runner, "all_tags on empty multimap returns empty") {
    std::multimap<std::string, std::string> empty;
    auto tags = all_tags(empty);
    ASSERT_EQ(tags.size(), 0u);
}

TESTKIT_MAIN(runner)
