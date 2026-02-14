// Exercise 04 -- Tests (read-only)
//
// Verifies the constrained SortedContainer class template.

#include <testkit/testkit.h>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("03-31-ex04: Constrained Class Template");

TEST(runner, "empty container has size zero") {
    SortedContainer<int> c;
    ASSERT_EQ(c.size(), std::size_t(0));
}

TEST(runner, "insert adds elements") {
    SortedContainer<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(7);
    ASSERT_EQ(c.size(), std::size_t(3));
}

TEST(runner, "elements are stored in sorted order") {
    SortedContainer<int> c;
    c.insert(30);
    c.insert(10);
    c.insert(20);
    ASSERT_EQ(c.at(0), 10);
    ASSERT_EQ(c.at(1), 20);
    ASSERT_EQ(c.at(2), 30);
}

TEST(runner, "contains finds existing elements") {
    SortedContainer<int> c;
    c.insert(5);
    c.insert(10);
    c.insert(15);
    ASSERT_TRUE(c.contains(10));
    ASSERT_FALSE(c.contains(7));
}

TEST(runner, "insert handles duplicates") {
    SortedContainer<int> c;
    c.insert(5);
    c.insert(5);
    c.insert(5);
    ASSERT_EQ(c.size(), std::size_t(3));
    ASSERT_TRUE(c.contains(5));
}

TEST(runner, "works with std::string") {
    SortedContainer<std::string> c;
    c.insert("cherry");
    c.insert("apple");
    c.insert("banana");
    ASSERT_EQ(c.at(0), std::string("apple"));
    ASSERT_EQ(c.at(1), std::string("banana"));
    ASSERT_EQ(c.at(2), std::string("cherry"));
}

TEST(runner, "Comparable concept accepts int and string") {
    // Gate: insert must work first
    SortedContainer<int> c;
    c.insert(1);

    ASSERT_TRUE(Comparable<int>);
    ASSERT_TRUE(Comparable<std::string>);
    ASSERT_TRUE(Comparable<double>);
}

TEST(runner, "contains returns false for empty container") {
    SortedContainer<int> c;
    ASSERT_FALSE(c.contains(42));
}

// NOTE: The following should NOT compile:
//   struct NoCompare {};
//   SortedContainer<NoCompare> c;
// The Comparable concept should reject types without < and ==.

TESTKIT_MAIN(runner)
