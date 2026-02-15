// Exercise 01 -- Tests (read-only)
//
// Verifies to_string and method_from_string conversions for HTTP methods.

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>
#include "ex01.h"

static testkit::TestRunner runner("05-49-ex01: HTTP Method Enum");

TEST(runner, "to_string converts GET") {
    ASSERT_EQ(to_string(Method::GET), std::string("GET"));
}

TEST(runner, "to_string converts POST") {
    ASSERT_EQ(to_string(Method::POST), std::string("POST"));
}

TEST(runner, "to_string converts PUT") {
    ASSERT_EQ(to_string(Method::PUT), std::string("PUT"));
}

TEST(runner, "to_string converts DELETE_ to DELETE") {
    ASSERT_EQ(to_string(Method::DELETE_), std::string("DELETE"));
}

TEST(runner, "to_string converts PATCH") {
    ASSERT_EQ(to_string(Method::PATCH), std::string("PATCH"));
}

TEST(runner, "to_string converts HEAD and OPTIONS") {
    ASSERT_EQ(to_string(Method::HEAD), std::string("HEAD"));
    ASSERT_EQ(to_string(Method::OPTIONS), std::string("OPTIONS"));
}

TEST(runner, "method_from_string parses GET") {
    ASSERT_TRUE(method_from_string("GET") == Method::GET);
}

TEST(runner, "method_from_string parses DELETE") {
    ASSERT_TRUE(method_from_string("DELETE") == Method::DELETE_);
}

TEST(runner, "method_from_string throws for unknown method") {
    ASSERT_THROWS(method_from_string("FOOBAR"), std::invalid_argument);
}

TEST(runner, "round-trip all methods") {
    Method methods[] = {
        Method::GET, Method::POST, Method::PUT,
        Method::DELETE_, Method::PATCH, Method::HEAD, Method::OPTIONS
    };
    for (auto m : methods) {
        ASSERT_TRUE(method_from_string(to_string(m)) == m);
    }
}

TESTKIT_MAIN(runner)
