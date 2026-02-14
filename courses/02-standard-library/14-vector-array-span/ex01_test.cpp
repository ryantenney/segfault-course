// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("02-14-ex01: Populate a Vector");

TEST(runner, "make_vector_with_list returns {10, 20, 30, 40, 50}") {
    auto v = make_vector_with_list();
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v[0], 10);
    ASSERT_EQ(v[1], 20);
    ASSERT_EQ(v[2], 30);
    ASSERT_EQ(v[3], 40);
    ASSERT_EQ(v[4], 50);
}

TEST(runner, "make_vector_push_back returns {1, 2, 3, 4}") {
    auto v = make_vector_push_back();
    ASSERT_EQ(v.size(), 4u);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
}

TEST(runner, "make_vector_emplace builds pairs in-place") {
    auto v = make_vector_emplace();
    ASSERT_EQ(v.size(), 3u);
    ASSERT_EQ(v[0].first, std::string("alice"));
    ASSERT_EQ(v[0].second, 90);
    ASSERT_EQ(v[1].first, std::string("bob"));
    ASSERT_EQ(v[1].second, 85);
    ASSERT_EQ(v[2].first, std::string("carol"));
    ASSERT_EQ(v[2].second, 92);
}

TESTKIT_MAIN(runner)
