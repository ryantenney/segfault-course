// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("02-19-ex03: Capture by Value");

TEST(runner, "make_counter starts from initial value") {
    auto counter = make_counter(0);
    ASSERT_EQ(counter(), 0);
}

TEST(runner, "make_counter increments on each call") {
    auto counter = make_counter(5);
    ASSERT_EQ(counter(), 5);
    ASSERT_EQ(counter(), 6);
    ASSERT_EQ(counter(), 7);
}

TEST(runner, "make_counter instances are independent") {
    auto c1 = make_counter(0);
    auto c2 = make_counter(100);
    ASSERT_EQ(c1(), 0);
    ASSERT_EQ(c2(), 100);
    ASSERT_EQ(c1(), 1);
    ASSERT_EQ(c2(), 101);
}

TEST(runner, "demonstrate_value_capture shows original unchanged") {
    auto [last, original] = demonstrate_value_capture(10, 3);
    // lambda increments copy 3 times: returns 10, 11, 12 -- last is 12
    ASSERT_EQ(last, 12);
    ASSERT_EQ(original, 10);
}

TEST(runner, "demonstrate_value_capture with zero calls") {
    auto [last, original] = demonstrate_value_capture(5, 0);
    // no calls, last return value is the initial value unchanged
    ASSERT_EQ(last, 5);
    ASSERT_EQ(original, 5);
}

TEST(runner, "demonstrate_value_capture with one call") {
    auto [last, original] = demonstrate_value_capture(0, 1);
    ASSERT_EQ(last, 0);
    ASSERT_EQ(original, 0);
}

TEST(runner, "accumulate_calls appends strings") {
    auto acc = accumulate_calls("start");
    ASSERT_EQ(acc("-a"), std::string("start-a"));
    ASSERT_EQ(acc("-b"), std::string("start-a-b"));
    ASSERT_EQ(acc("-c"), std::string("start-a-b-c"));
}

TEST(runner, "accumulate_calls with empty initial") {
    auto acc = accumulate_calls("");
    ASSERT_EQ(acc("hello"), std::string("hello"));
    ASSERT_EQ(acc(" world"), std::string("hello world"));
}

TESTKIT_MAIN(runner)
