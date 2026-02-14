// Exercise 08 -- Tests (read-only)

#include <cstring>
#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-10-ex08: Custom Deleter");

TEST(runner, "make_c_string creates a valid C string") {
    auto cs = make_c_string("hello");
    ASSERT_TRUE(cs != nullptr);
    ASSERT_EQ(std::strcmp(cs.get(), "hello"), 0);
}

TEST(runner, "make_c_string handles empty string") {
    auto cs = make_c_string("");
    ASSERT_TRUE(cs != nullptr);
    ASSERT_EQ(std::strcmp(cs.get(), ""), 0);
}

TEST(runner, "create_resource calls destroy_resource on destruction") {
    deleter_call_count() = 0;
    {
        auto r = create_resource(42);
        ASSERT_EQ(r->id, 42);
        ASSERT_EQ(deleter_call_count(), 0);
    }
    // After scope exit, destroy_resource should have been called once
    ASSERT_EQ(deleter_call_count(), 1);
}

TEST(runner, "make_int_array uses lambda deleter") {
    deleter_call_count() = 0;
    {
        auto arr = make_int_array(5);
        ASSERT_TRUE(arr != nullptr);
        // Write to the array to verify it's usable
        for (std::size_t i = 0; i < 5; ++i) {
            arr[i] = static_cast<int>(i * 10);
        }
        ASSERT_EQ(arr[0], 0);
        ASSERT_EQ(arr[4], 40);
        ASSERT_EQ(deleter_call_count(), 0);
    }
    ASSERT_EQ(deleter_call_count(), 1);
}

TESTKIT_MAIN(runner)
