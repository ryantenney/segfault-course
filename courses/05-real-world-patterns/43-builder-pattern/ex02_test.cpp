// Exercise 02 -- Tests (read-only)
//
// Verifies that RequestBuilder setters return *this for chaining.

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("05-43-ex02: Method Chaining");

TEST(runner, "set_method returns reference to same builder") {
    RequestBuilder b;
    RequestBuilder& ref = b.set_method("GET");
    ASSERT_EQ(&ref, &b);
}

TEST(runner, "set_url returns reference to same builder") {
    RequestBuilder b;
    RequestBuilder& ref = b.set_url("/path");
    ASSERT_EQ(&ref, &b);
}

TEST(runner, "set_body returns reference to same builder") {
    RequestBuilder b;
    RequestBuilder& ref = b.set_body("payload");
    ASSERT_EQ(&ref, &b);
}

TEST(runner, "chained calls set all fields") {
    RequestBuilder b;
    b.set_method("POST").set_url("https://api.example.com").set_body("hello");
    ASSERT_EQ(b.get_method(), std::string("POST"));
    ASSERT_EQ(b.get_url(), std::string("https://api.example.com"));
    ASSERT_EQ(b.get_body(), std::string("hello"));
}

TEST(runner, "chaining works in any order") {
    RequestBuilder b;
    b.set_body("data").set_method("PUT").set_url("/update");
    ASSERT_EQ(b.get_method(), std::string("PUT"));
    ASSERT_EQ(b.get_url(), std::string("/update"));
    ASSERT_EQ(b.get_body(), std::string("data"));
}

TEST(runner, "chain can override previous values") {
    RequestBuilder b;
    b.set_method("GET").set_method("POST").set_url("/v1").set_url("/v2");
    ASSERT_EQ(b.get_method(), std::string("POST"));
    ASSERT_EQ(b.get_url(), std::string("/v2"));
}

TESTKIT_MAIN(runner)
