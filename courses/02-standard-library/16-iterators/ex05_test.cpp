// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("02-16-ex05: Iterator Arithmetic");

TEST(runner, "get_nth returns the element at index 0") {
    std::list<int> lst = {10, 20, 30};
    ASSERT_EQ(get_nth(lst, 0), 10);
}

TEST(runner, "get_nth returns the element at a middle index") {
    std::list<int> lst = {10, 20, 30, 40, 50};
    ASSERT_EQ(get_nth(lst, 2), 30);
}

TEST(runner, "get_nth returns the last element") {
    std::list<int> lst = {10, 20, 30};
    ASSERT_EQ(get_nth(lst, 2), 30);
}

TEST(runner, "distance_between returns distance between elements") {
    std::list<std::string> lst = {"a", "b", "c", "d", "e"};
    ASSERT_EQ(distance_between(lst, "b", "d"), 2);
}

TEST(runner, "distance_between returns negative for reversed order") {
    std::list<std::string> lst = {"a", "b", "c", "d", "e"};
    ASSERT_EQ(distance_between(lst, "d", "b"), -2);
}

TEST(runner, "distance_between returns -1 when element not found") {
    std::list<std::string> lst = {"a", "b", "c"};
    ASSERT_EQ(distance_between(lst, "a", "z"), -1);
}

TEST(runner, "advance_and_read returns element at stepped position") {
    std::list<std::string> lst = {"zero", "one", "two", "three"};
    ASSERT_EQ(advance_and_read(lst, 0), std::string("zero"));
    ASSERT_EQ(advance_and_read(lst, 2), std::string("two"));
    ASSERT_EQ(advance_and_read(lst, 3), std::string("three"));
}

TEST(runner, "get_middle returns the middle element") {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    ASSERT_EQ(get_middle(vec), 30); // index 2
}

TEST(runner, "get_middle with even size") {
    std::vector<int> vec = {1, 2, 3, 4};
    ASSERT_EQ(get_middle(vec), 3); // index 2
}

TEST(runner, "get_middle with single element") {
    std::vector<int> vec = {99};
    ASSERT_EQ(get_middle(vec), 99); // index 0
}

TESTKIT_MAIN(runner)
