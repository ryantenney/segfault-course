// Exercise 01 -- Tests (read-only)
//
// Verifies that RequestBuilder stores method, url, and body correctly.

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("05-43-ex01: Basic Builder");

TEST(runner, "set_method stores the method") {
    RequestBuilder b;
    b.set_method("POST");
    ASSERT_EQ(b.get_method(), std::string("POST"));
}

TEST(runner, "set_url stores the url") {
    RequestBuilder b;
    b.set_url("https://example.com/api");
    ASSERT_EQ(b.get_url(), std::string("https://example.com/api"));
}

TEST(runner, "set_body stores the body") {
    RequestBuilder b;
    b.set_body("{\"key\":\"value\"}");
    ASSERT_EQ(b.get_body(), std::string("{\"key\":\"value\"}"));
}

TEST(runner, "default values are empty strings") {
    RequestBuilder b;
    ASSERT_EQ(b.get_method(), std::string(""));
    ASSERT_EQ(b.get_url(), std::string(""));
    ASSERT_EQ(b.get_body(), std::string(""));
}

TEST(runner, "setters can be called multiple times") {
    RequestBuilder b;
    b.set_method("GET");
    b.set_method("PUT");
    ASSERT_EQ(b.get_method(), std::string("PUT"));
}

TEST(runner, "all fields can be set independently") {
    RequestBuilder b;
    b.set_method("DELETE");
    b.set_url("/items/42");
    b.set_body("");
    ASSERT_EQ(b.get_method(), std::string("DELETE"));
    ASSERT_EQ(b.get_url(), std::string("/items/42"));
    ASSERT_EQ(b.get_body(), std::string(""));
}

TESTKIT_MAIN(runner)
