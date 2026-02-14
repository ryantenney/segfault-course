// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("03-26-ex07: Subscript Operator");

TEST(runner, "size returns the number of elements") {
    FixedArray arr;
    ASSERT_EQ(arr.size(), std::size_t(5));
}

TEST(runner, "non-const operator[] allows writing") {
    FixedArray arr;
    arr[0] = 10;
    arr[1] = 20;
    arr[4] = 50;
    ASSERT_EQ(arr[0], 10);
    ASSERT_EQ(arr[1], 20);
    ASSERT_EQ(arr[4], 50);
}

TEST(runner, "elements are default-initialized to zero") {
    FixedArray arr;
    for (std::size_t i = 0; i < arr.size(); ++i) {
        ASSERT_EQ(arr[i], 0);
    }
}

TEST(runner, "const operator[] provides read-only access") {
    FixedArray arr;
    arr[2] = 42;
    const FixedArray& cref = arr;
    ASSERT_EQ(cref[2], 42);
}

TEST(runner, "operator[] on const object returns const reference") {
    FixedArray arr;
    arr[0] = 99;
    const FixedArray& cref = arr;
    // The following should compile — reading from const is fine
    int val = cref[0];
    ASSERT_EQ(val, 99);
}

TEST(runner, "out-of-range index throws std::out_of_range") {
    FixedArray arr;
    ASSERT_THROWS(arr[5], std::out_of_range);
    ASSERT_THROWS(arr[100], std::out_of_range);
}

TEST(runner, "out-of-range on const throws std::out_of_range") {
    const FixedArray arr;
    ASSERT_THROWS(arr[5], std::out_of_range);
}

TEST(runner, "modifying through operator[] changes the stored value") {
    FixedArray arr;
    arr[3] = 7;
    ASSERT_EQ(arr[3], 7);
    arr[3] = 14;
    ASSERT_EQ(arr[3], 14);
}

TESTKIT_MAIN(runner)
