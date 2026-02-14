// Exercise 08 -- Tests (read-only)
//
// Verifies ad-hoc requires expressions.

#include <testkit/testkit.h>
#include <string>
#include "ex08.h"

// A custom type with a length() method.
struct Buffer {
    std::size_t capacity;
    std::size_t length() const { return capacity; }
};

// A custom type with to_string via ADL.
struct Point {
    int x, y;
};

// Free function found via ADL (same namespace as Point, which is global here).
inline std::string to_string(const Point& p) {
    return "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
}

static testkit::TestRunner runner("03-31-ex08: Ad-Hoc Requires Expression");

TEST(runner, "get_length works with std::string") {
    std::string s = "hello";
    ASSERT_EQ(get_length(s), std::size_t(5));
}

TEST(runner, "get_length works with empty string") {
    std::string s;
    ASSERT_EQ(get_length(s), std::size_t(0));
}

TEST(runner, "get_length works with Buffer") {
    Buffer buf{1024};
    ASSERT_EQ(get_length(buf), std::size_t(1024));
}

TEST(runner, "serialize_pair with two ints") {
    std::string result = serialize_pair(1, 2);
    ASSERT_EQ(result, std::string("(1, 2)"));
}

TEST(runner, "serialize_pair with int and double") {
    std::string result = serialize_pair(42, 3.14);
    ASSERT_TRUE(result.substr(0, 4) == "(42,");
    ASSERT_TRUE(result.find("3.14") != std::string::npos);
    ASSERT_TRUE(result.back() == ')');
}

TEST(runner, "serialize_pair with Point") {
    Point p{5, 10};
    std::string result = serialize_pair(p, 99);
    ASSERT_EQ(result, std::string("((5,10), 99)"));
}

TEST(runner, "serialize_pair with two Points") {
    Point a{1, 2}, b{3, 4};
    std::string result = serialize_pair(a, b);
    ASSERT_EQ(result, std::string("((1,2), (3,4))"));
}

// NOTE: The following should NOT compile:
//   struct Opaque {};
//   get_length(Opaque{});     // no .length() method
//   serialize_pair(Opaque{}, 1);  // no to_string for Opaque

TESTKIT_MAIN(runner)
