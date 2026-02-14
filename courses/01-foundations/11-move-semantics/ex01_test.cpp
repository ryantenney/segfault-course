// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-11-ex01: Move a String into a Container");

TEST(runner, "add_by_copy triggers a copy") {
    std::vector<TrackedString> vec;
    vec.reserve(4); // prevent reallocation moves
    TrackedString item("hello");
    TrackedString::log.clear();
    add_by_copy(vec, std::move(item));
    // item was moved into the parameter, then copied into vec
    ASSERT_TRUE(TrackedString::log.find("copy") != std::string::npos);
}

TEST(runner, "add_by_move triggers a move, not a copy") {
    std::vector<TrackedString> vec;
    vec.reserve(4);
    TrackedString item("world");
    TrackedString::log.clear();
    add_by_move(vec, std::move(item));
    // item was moved into parameter, then moved into vec -- no "copy"
    ASSERT_TRUE(TrackedString::log.find("copy") == std::string::npos);
    ASSERT_TRUE(TrackedString::log.find("move") != std::string::npos);
}

TEST(runner, "add_by_move puts the correct value in the vector") {
    std::vector<TrackedString> vec;
    vec.reserve(4);
    TrackedString item("test");
    add_by_move(vec, std::move(item));
    ASSERT_EQ(vec.back().value, std::string("test"));
}

TEST(runner, "build_collection creates the correct elements") {
    auto result = build_collection({"alpha", "beta", "gamma"});
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0].value, std::string("alpha"));
    ASSERT_EQ(result[1].value, std::string("beta"));
    ASSERT_EQ(result[2].value, std::string("gamma"));
}

TESTKIT_MAIN(runner)
