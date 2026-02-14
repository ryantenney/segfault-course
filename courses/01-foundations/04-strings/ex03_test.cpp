// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-04-ex03: Substring Without Allocation");

TEST(runner, "first_n returns the first n characters") {
    ASSERT_EQ(first_n("hello world", 5), std::string_view("hello"));
    ASSERT_EQ(first_n("hi", 10), std::string_view("hi"));
    ASSERT_EQ(first_n("abc", 0), std::string_view(""));
}

TEST(runner, "last_n returns the last n characters") {
    ASSERT_EQ(last_n("hello world", 5), std::string_view("world"));
    ASSERT_EQ(last_n("hi", 10), std::string_view("hi"));
    ASSERT_EQ(last_n("abc", 0), std::string_view(""));
}

TEST(runner, "drop_first_n removes leading characters") {
    ASSERT_EQ(drop_first_n("hello world", 6), std::string_view("world"));
    ASSERT_EQ(drop_first_n("abc", 0), std::string_view("abc"));
    ASSERT_EQ(drop_first_n("abc", 5), std::string_view(""));
}

TEST(runner, "slice extracts a range") {
    ASSERT_EQ(slice("hello world", 3, 8), std::string_view("lo wo"));
    ASSERT_EQ(slice("abcdef", 0, 3), std::string_view("abc"));
    ASSERT_EQ(slice("abcdef", 4, 100), std::string_view("ef"));
    ASSERT_EQ(slice("abcdef", 10, 20), std::string_view(""));
}

TEST(runner, "results share memory with the original string") {
    const char* data = "hello world";
    std::string_view sv(data);
    std::string_view result = first_n(sv, 5);
    // The returned view should point into the same memory
    ASSERT_EQ(result.data(), sv.data());
}

TESTKIT_MAIN(runner)
