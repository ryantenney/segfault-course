// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("02-17-ex06: Accumulate and Reduce");

TEST(runner, "sum_all returns the sum of all elements") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    ASSERT_EQ(sum_all(vec), 15);
}

TEST(runner, "sum_all with empty vector returns 0") {
    std::vector<int> vec;
    ASSERT_EQ(sum_all(vec), 0);
}

TEST(runner, "sum_all with negative numbers") {
    std::vector<int> vec = {-5, 3, -2, 10};
    ASSERT_EQ(sum_all(vec), 6);
}

TEST(runner, "product_all returns the product of all elements") {
    std::vector<int> vec = {2, 3, 4};
    ASSERT_EQ(product_all(vec), 24LL);
}

TEST(runner, "product_all with empty vector returns 1") {
    std::vector<int> vec;
    ASSERT_EQ(product_all(vec), 1LL);
}

TEST(runner, "product_all with a zero element") {
    std::vector<int> vec = {5, 0, 3};
    ASSERT_EQ(product_all(vec), 0LL);
}

TEST(runner, "concat_strings joins with separator") {
    std::vector<std::string> vec = {"hello", "world", "foo"};
    ASSERT_EQ(concat_strings(vec, ", "), std::string("hello, world, foo"));
}

TEST(runner, "concat_strings with single element") {
    std::vector<std::string> vec = {"only"};
    ASSERT_EQ(concat_strings(vec, "-"), std::string("only"));
}

TEST(runner, "concat_strings with empty vector") {
    std::vector<std::string> vec;
    ASSERT_EQ(concat_strings(vec, ","), std::string(""));
}

TEST(runner, "dot_product computes correctly") {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    ASSERT_EQ(dot_product(a, b), 32);
}

TEST(runner, "dot_product with zeros") {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {0, 0, 0};
    ASSERT_EQ(dot_product(a, b), 0);
}

TEST(runner, "dot_product with empty vectors") {
    std::vector<int> a;
    std::vector<int> b;
    ASSERT_EQ(dot_product(a, b), 0);
}

TESTKIT_MAIN(runner)
