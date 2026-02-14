// Exercise 05 — Tests (read-only)
//
// Verifies const_cast usage for interfacing with legacy APIs.

#include <cstring>
#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("01-08-ex05: const_cast for Legacy APIs");

TEST(runner, "safe_strlen computes length of const string") {
    const char* msg = "Hello";
    ASSERT_EQ(safe_strlen(msg), 5);
    ASSERT_EQ(safe_strlen(""), 0);
    ASSERT_EQ(safe_strlen("C++ casts"), 9);
}

TEST(runner, "safe_copy copies from const source") {
    const char* src = "World";
    char dest[16] = {};
    safe_copy(dest, src, 5);
    ASSERT_EQ(std::string(dest, 5), std::string("World"));
}

TEST(runner, "to_string creates std::string from const C string") {
    const char* msg = "Modern C++";
    ASSERT_EQ(to_string(msg), std::string("Modern C++"));
    ASSERT_EQ(to_string(""), std::string(""));
}

TESTKIT_MAIN(runner)
