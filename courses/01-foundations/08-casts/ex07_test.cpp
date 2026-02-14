// Exercise 07 — Tests (read-only)
//
// Verifies the type-safe Container template that eliminates casts.

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("01-08-ex07: Eliminate a Cast");

TEST(runner, "Container<int> stores and retrieves") {
    Container<int> c;
    c.store(42);
    ASSERT_EQ(c.retrieve(), 42);
}

TEST(runner, "Container<double> stores and retrieves") {
    Container<double> c;
    c.store(3.14);
    ASSERT_EQ(c.retrieve(), 3.14);
}

TEST(runner, "Container<std::string> stores and retrieves") {
    Container<std::string> c;
    c.store("hello");
    ASSERT_EQ(c.retrieve(), std::string("hello"));
}

TEST(runner, "store_and_get_int round-trips value") {
    ASSERT_EQ(store_and_get_int(99), 99);
    ASSERT_EQ(store_and_get_int(-5), -5);
    ASSERT_EQ(store_and_get_int(0), 0);
}

TEST(runner, "store_and_get_string round-trips value") {
    ASSERT_EQ(store_and_get_string("C++"), std::string("C++"));
    ASSERT_EQ(store_and_get_string(""), std::string(""));
}

TESTKIT_MAIN(runner)
