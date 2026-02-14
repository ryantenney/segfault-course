// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-06-ex02: auto with const/reference");

TEST(runner, "first_copy returns a copy of the first element") {
    std::vector<int> v = {10, 20, 30};
    int val = first_copy(v);
    ASSERT_EQ(val, 10);
    // Modifying val should not affect the vector
    val = 999;
    ASSERT_EQ(v[0], 10);
}

TEST(runner, "last_ref returns a reference to the last element") {
    std::vector<std::string> v = {"alpha", "beta", "gamma"};
    const std::string& ref = last_ref(v);
    ASSERT_EQ(ref, "gamma");
    // The reference should point into the vector's storage
    ASSERT_EQ(&ref, &v.back());
}

TEST(runner, "double_all multiplies each element by 2") {
    std::vector<int> v = {1, 2, 3, 4};
    double_all(v);
    ASSERT_EQ(v[0], 2);
    ASSERT_EQ(v[1], 4);
    ASSERT_EQ(v[2], 6);
    ASSERT_EQ(v[3], 8);
}

TEST(runner, "double_all handles empty vector") {
    std::vector<int> v;
    double_all(v);
    ASSERT_TRUE(v.empty());
}

TEST(runner, "count_long_strings counts strings exceeding threshold") {
    std::vector<std::string> v = {"hi", "hello", "hey", "greetings"};
    ASSERT_EQ(count_long_strings(v, 3), 2);  // "hello" and "greetings"
    ASSERT_EQ(count_long_strings(v, 0), 4);  // all have length > 0
    ASSERT_EQ(count_long_strings(v, 100), 0);
}

TESTKIT_MAIN(runner)
