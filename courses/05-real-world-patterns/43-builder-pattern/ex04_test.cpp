// Exercise 04 -- Tests (read-only)
//
// Verifies that build() returns nullopt when required fields are missing.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("05-43-ex04: Required vs Optional Fields");

TEST(runner, "build succeeds with method and url") {
    RequestBuilder b;
    auto r = b.set_method("GET").set_url("/api").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->method, std::string("GET"));
    ASSERT_EQ(r->url, std::string("/api"));
}

TEST(runner, "build succeeds with all fields") {
    RequestBuilder b;
    auto r = b.set_method("POST").set_url("/data").set_body("payload").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->body, std::string("payload"));
}

TEST(runner, "build fails when url is missing") {
    RequestBuilder b;
    auto r = b.set_method("GET").build();
    ASSERT_FALSE(r.has_value());
}

TEST(runner, "build fails when method is missing") {
    RequestBuilder b;
    auto r = b.set_url("/api").build();
    ASSERT_FALSE(r.has_value());
}

TEST(runner, "build fails when both method and url are missing") {
    RequestBuilder b;
    auto r = b.build();
    ASSERT_FALSE(r.has_value());
}

TEST(runner, "body is optional and defaults to empty") {
    RequestBuilder b;
    auto r = b.set_method("GET").set_url("/health").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->body, std::string(""));
}

TEST(runner, "build fails when url is empty string") {
    RequestBuilder b;
    auto r = b.set_method("GET").set_url("").build();
    ASSERT_FALSE(r.has_value());
}

TESTKIT_MAIN(runner)
