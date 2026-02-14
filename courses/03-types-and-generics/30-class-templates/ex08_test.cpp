// Exercise 08 -- Tests (read-only)
//
// Verifies that functions using dependent type names work correctly.

#include <testkit/testkit.h>
#include <string>
#include <vector>
#include <list>
#include "ex08.h"

static testkit::TestRunner runner("03-30-ex08: Dependent Type Names");

TEST(runner, "get_first returns first element of vector<int>") {
    std::vector<int> v{10, 20, 30};
    ASSERT_EQ(get_first(v), 10);
}

TEST(runner, "get_first returns first element of vector<string>") {
    std::vector<std::string> v{"alpha", "beta"};
    ASSERT_EQ(get_first(v), std::string("alpha"));
}

TEST(runner, "get_first works with std::list") {
    std::list<int> lst{42, 99};
    ASSERT_EQ(get_first(lst), 42);
}

TEST(runner, "get_size returns correct count for vector") {
    std::vector<int> v{1, 2, 3, 4, 5};
    ASSERT_EQ(get_size(v), std::size_t(5));
}

TEST(runner, "get_size returns 0 for empty vector") {
    std::vector<double> v;
    ASSERT_EQ(get_size(v), std::size_t(0));
}

TEST(runner, "get_begin returns iterator to first element") {
    std::vector<int> v{7, 8, 9};
    auto it = get_begin(v);
    ASSERT_EQ(*it, 7);
}

TEST(runner, "get_begin works with list") {
    std::list<std::string> lst{"hello", "world"};
    auto it = get_begin(lst);
    ASSERT_EQ(*it, std::string("hello"));
}

TEST(runner, "find_or_default returns target when found") {
    std::vector<int> v{10, 20, 30, 40};
    ASSERT_EQ(find_or_default(v, 30), 30);
}

TEST(runner, "find_or_default returns default when not found") {
    std::vector<int> v{10, 20, 30};
    ASSERT_EQ(find_or_default(v, 99), 0);
}

TEST(runner, "find_or_default works with strings") {
    std::vector<std::string> v{"apple", "banana", "cherry"};
    ASSERT_EQ(find_or_default(v, std::string("banana")), std::string("banana"));
    ASSERT_EQ(find_or_default(v, std::string("grape")), std::string(""));
}

TESTKIT_MAIN(runner)
