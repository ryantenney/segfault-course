// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("02-16-ex07: Insert Iterator");

TEST(runner, "vector_to_set creates a set from a vector") {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    auto s = vector_to_set(vec);
    // Set removes duplicates and sorts
    ASSERT_EQ(s.size(), 7u);
    ASSERT_TRUE(s.count(1) == 1);
    ASSERT_TRUE(s.count(3) == 1);
    ASSERT_TRUE(s.count(9) == 1);
}

TEST(runner, "vector_to_set with empty vector") {
    std::vector<int> vec;
    auto s = vector_to_set(vec);
    ASSERT_TRUE(s.empty());
}

TEST(runner, "vector_to_set deduplicates") {
    std::vector<int> vec = {5, 5, 5, 5};
    auto s = vector_to_set(vec);
    ASSERT_EQ(s.size(), 1u);
}

TEST(runner, "merge_sets adds elements from b to a") {
    std::set<int> a = {1, 3, 5};
    std::set<int> b = {2, 4, 6};
    merge_sets(a, b);
    ASSERT_EQ(a.size(), 6u);
    ASSERT_TRUE(a.count(2) == 1);
    ASSERT_TRUE(a.count(4) == 1);
    ASSERT_TRUE(a.count(6) == 1);
}

TEST(runner, "merge_sets handles overlapping elements") {
    std::set<int> a = {1, 2, 3};
    std::set<int> b = {2, 3, 4};
    merge_sets(a, b);
    ASSERT_EQ(a.size(), 4u); // {1, 2, 3, 4}
}

TEST(runner, "merge_sets with empty b leaves a unchanged") {
    std::set<int> a = {10, 20};
    std::set<int> b;
    merge_sets(a, b);
    ASSERT_EQ(a.size(), 2u);
}

TEST(runner, "insert_at_front inserts at the beginning of the list") {
    std::list<int> lst = {4, 5};
    std::vector<int> src = {1, 2, 3};
    insert_at_front(lst, src);
    // inserter(lst, lst.begin()) inserts each element at the beginning
    // successively, so {1,2,3} inserted one-by-one at begin => {1, 2, 3, 4, 5}
    ASSERT_EQ(lst.size(), 5u);
    auto it = lst.begin();
    ASSERT_EQ(*it, 1); ++it;
    ASSERT_EQ(*it, 2); ++it;
    ASSERT_EQ(*it, 3); ++it;
    ASSERT_EQ(*it, 4); ++it;
    ASSERT_EQ(*it, 5);
}

TEST(runner, "insert_at_front with empty source does nothing") {
    std::list<int> lst = {1, 2};
    std::vector<int> src;
    insert_at_front(lst, src);
    ASSERT_EQ(lst.size(), 2u);
}

TESTKIT_MAIN(runner)
