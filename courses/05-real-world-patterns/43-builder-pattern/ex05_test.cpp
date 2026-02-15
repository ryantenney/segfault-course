// Exercise 05 -- Tests (read-only)
//
// Verifies that the builder applies sensible defaults.

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("05-43-ex05: Builder with Defaults");

TEST(runner, "method defaults to GET") {
    RequestBuilder b;
    auto r = b.set_url("/api").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->method, std::string("GET"));
}

TEST(runner, "method can be overridden") {
    RequestBuilder b;
    auto r = b.set_url("/api").set_method("POST").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->method, std::string("POST"));
}

TEST(runner, "headers default to empty") {
    RequestBuilder b;
    auto r = b.set_url("/api").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_TRUE(r->headers.empty());
}

TEST(runner, "headers accumulate with add_header") {
    RequestBuilder b;
    auto r = b.set_url("/api")
              .add_header("Content-Type", "application/json")
              .add_header("Authorization", "Bearer xyz")
              .build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->headers.size(), std::size_t(2));
    ASSERT_EQ(r->headers[0].first, std::string("Content-Type"));
    ASSERT_EQ(r->headers[0].second, std::string("application/json"));
    ASSERT_EQ(r->headers[1].first, std::string("Authorization"));
    ASSERT_EQ(r->headers[1].second, std::string("Bearer xyz"));
}

TEST(runner, "url is still required") {
    RequestBuilder b;
    auto r = b.set_method("POST").build();
    ASSERT_FALSE(r.has_value());
}

TEST(runner, "body defaults to empty") {
    RequestBuilder b;
    auto r = b.set_url("/test").build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->body, std::string(""));
}

TEST(runner, "full build with all fields and defaults") {
    RequestBuilder b;
    auto r = b.set_url("/submit")
              .set_body("data")
              .add_header("X-Custom", "val")
              .build();
    ASSERT_TRUE(r.has_value());
    ASSERT_EQ(r->method, std::string("GET"));
    ASSERT_EQ(r->url, std::string("/submit"));
    ASSERT_EQ(r->body, std::string("data"));
    ASSERT_EQ(r->headers.size(), std::size_t(1));
}

TESTKIT_MAIN(runner)
