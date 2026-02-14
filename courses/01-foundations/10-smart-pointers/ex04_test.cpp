// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-10-ex04: unique_ptr in Containers");

TEST(runner, "make_parts creates the correct number of parts") {
    auto parts = make_parts({"A1", "B2", "C3"});
    ASSERT_EQ(parts.size(), 3u);
}

TEST(runner, "make_parts assigns correct codes") {
    auto parts = make_parts({"X", "Y"});
    ASSERT_EQ(parts[0]->code, std::string("X"));
    ASSERT_EQ(parts[1]->code, std::string("Y"));
}

TEST(runner, "count_parts counts non-null elements") {
    auto parts = make_parts({"A", "B", "C"});
    ASSERT_EQ(count_parts(parts), 3u);
    parts[1].reset(); // null out the middle one
    ASSERT_EQ(count_parts(parts), 2u);
}

TEST(runner, "pop_part removes and returns the last element") {
    auto parts = make_parts({"First", "Last"});
    auto popped = pop_part(parts);
    ASSERT_EQ(popped->code, std::string("Last"));
    ASSERT_EQ(parts.size(), 1u);
}

TEST(runner, "merge_parts moves all elements from source to dest") {
    auto src = make_parts({"S1", "S2"});
    auto dst = make_parts({"D1"});
    merge_parts(src, dst);
    ASSERT_TRUE(src.empty());
    ASSERT_EQ(dst.size(), 3u);
    ASSERT_EQ(dst[0]->code, std::string("D1"));
    ASSERT_EQ(dst[1]->code, std::string("S1"));
    ASSERT_EQ(dst[2]->code, std::string("S2"));
}

TESTKIT_MAIN(runner)
