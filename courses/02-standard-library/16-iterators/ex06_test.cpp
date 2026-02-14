// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("02-16-ex06: Back-Inserter");

TEST(runner, "copy_to_vector copies all elements") {
    std::list<int> lst = {10, 20, 30};
    auto vec = copy_to_vector(lst);
    ASSERT_EQ(vec.size(), 3u);
    ASSERT_EQ(vec[0], 10);
    ASSERT_EQ(vec[1], 20);
    ASSERT_EQ(vec[2], 30);
}

TEST(runner, "copy_to_vector with empty list") {
    std::list<int> lst;
    auto vec = copy_to_vector(lst);
    ASSERT_TRUE(vec.empty());
}

TEST(runner, "transform_to_vector applies function to each element") {
    std::vector<int> src = {1, 2, 3, 4};
    auto result = transform_to_vector(src, [](int x) { return x * x; });
    ASSERT_EQ(result.size(), 4u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
    ASSERT_EQ(result[3], 16);
}

TEST(runner, "transform_to_vector with negation") {
    std::vector<int> src = {5, -3, 0};
    auto result = transform_to_vector(src, [](int x) { return -x; });
    ASSERT_EQ(result[0], -5);
    ASSERT_EQ(result[1], 3);
    ASSERT_EQ(result[2], 0);
}

TEST(runner, "merge_vectors appends b to a") {
    std::vector<std::string> a = {"x", "y"};
    std::vector<std::string> b = {"z", "w"};
    merge_vectors(a, b);
    ASSERT_EQ(a.size(), 4u);
    ASSERT_EQ(a[0], std::string("x"));
    ASSERT_EQ(a[1], std::string("y"));
    ASSERT_EQ(a[2], std::string("z"));
    ASSERT_EQ(a[3], std::string("w"));
}

TEST(runner, "merge_vectors with empty b does nothing") {
    std::vector<std::string> a = {"a"};
    std::vector<std::string> b;
    merge_vectors(a, b);
    ASSERT_EQ(a.size(), 1u);
}

TEST(runner, "merge_vectors with empty a copies all of b") {
    std::vector<std::string> a;
    std::vector<std::string> b = {"hello", "world"};
    merge_vectors(a, b);
    ASSERT_EQ(a.size(), 2u);
    ASSERT_EQ(a[0], std::string("hello"));
    ASSERT_EQ(a[1], std::string("world"));
}

TESTKIT_MAIN(runner)
