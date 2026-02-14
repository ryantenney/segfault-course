// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("03-33-ex05: Emplace with Forwarding");

TEST(runner, "emplace_back adds elements") {
    MiniVec<std::string> v;
    v.emplace_back("hello");
    v.emplace_back("world");
    ASSERT_EQ(v.size(), 2u);
    ASSERT_EQ(v[0], std::string("hello"));
    ASSERT_EQ(v[1], std::string("world"));
}

TEST(runner, "emplace_back constructs string from count and char") {
    MiniVec<std::string> v;
    v.emplace_back(5, 'x');
    ASSERT_EQ(v.back(), std::string("xxxxx"));
}

TEST(runner, "emplace_back constructs Entry from args") {
    MiniVec<Entry> v;
    v.emplace_back("alpha", 1);
    ASSERT_EQ(v[0].name, std::string("alpha"));
    ASSERT_EQ(v[0].id, 1);
}

TEST(runner, "emplace_back avoids unnecessary copies") {
    MiniVec<Entry> v;
    v.emplace_back("beta", 2);
    // The entry in the vector should have been constructed from args
    // (possibly moved during vector reallocation, but not explicitly copied by us)
    ASSERT_EQ(v[0].name, std::string("beta"));
    ASSERT_EQ(v[0].id, 2);
}

TEST(runner, "emplace_back with rvalue string forwards correctly") {
    MiniVec<Entry> v;
    std::string name = "gamma";
    v.emplace_back(std::move(name), 3);
    ASSERT_EQ(v.back().name, std::string("gamma"));
    ASSERT_EQ(v.back().id, 3);
}

TEST(runner, "emplace_back works with multiple elements") {
    MiniVec<Entry> v;
    v.emplace_back("a", 1);
    v.emplace_back("b", 2);
    v.emplace_back("c", 3);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_EQ(v[2].name, std::string("c"));
    ASSERT_EQ(v[2].id, 3);
}

TESTKIT_MAIN(runner)
