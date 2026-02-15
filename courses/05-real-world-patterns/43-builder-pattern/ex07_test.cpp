// Exercise 07 -- Tests (read-only)
//
// Verifies nested builders compose correctly into a top-level object.

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("05-43-ex07: Nested Builder");

TEST(runner, "HeadersBuilder builds empty headers") {
    HeadersBuilder hb;
    Headers h = hb.build();
    ASSERT_TRUE(h.entries.empty());
}

TEST(runner, "HeadersBuilder accumulates entries") {
    HeadersBuilder hb;
    hb.add("Accept", "text/html").add("Host", "example.com");
    Headers h = hb.build();
    ASSERT_EQ(h.entries.size(), std::size_t(2));
    ASSERT_EQ(h.entries[0].first, std::string("Accept"));
    ASSERT_EQ(h.entries[1].second, std::string("example.com"));
}

TEST(runner, "BodyBuilder builds body with content and type") {
    BodyBuilder bb;
    bb.set_content("hello").set_content_type("text/plain");
    Body b = bb.build();
    ASSERT_EQ(b.content, std::string("hello"));
    ASSERT_EQ(b.content_type, std::string("text/plain"));
}

TEST(runner, "BodyBuilder defaults are empty") {
    BodyBuilder bb;
    Body b = bb.build();
    ASSERT_EQ(b.content, std::string(""));
    ASSERT_EQ(b.content_type, std::string(""));
}

TEST(runner, "RequestBuilder composes sub-builders") {
    RequestBuilder rb;
    rb.set_method("POST").set_url("/upload");
    rb.headers_builder().add("Authorization", "Bearer token");
    rb.body_builder().set_content("file data").set_content_type("application/octet-stream");

    HttpRequest req = rb.build();
    ASSERT_EQ(req.method, std::string("POST"));
    ASSERT_EQ(req.url, std::string("/upload"));
    ASSERT_EQ(req.headers.entries.size(), std::size_t(1));
    ASSERT_EQ(req.headers.entries[0].first, std::string("Authorization"));
    ASSERT_EQ(req.body.content, std::string("file data"));
    ASSERT_EQ(req.body.content_type, std::string("application/octet-stream"));
}

TEST(runner, "RequestBuilder with no sub-builder config") {
    RequestBuilder rb;
    rb.set_method("GET").set_url("/index");
    HttpRequest req = rb.build();
    ASSERT_EQ(req.method, std::string("GET"));
    ASSERT_EQ(req.url, std::string("/index"));
    ASSERT_TRUE(req.headers.entries.empty());
    ASSERT_EQ(req.body.content, std::string(""));
}

TEST(runner, "sub-builders return references for chaining") {
    RequestBuilder rb;
    rb.set_url("/test");
    HeadersBuilder& href = rb.headers_builder();
    BodyBuilder& bref = rb.body_builder();
    href.add("X-Test", "1");
    bref.set_content("data");
    HttpRequest req = rb.build();
    ASSERT_EQ(req.headers.entries.size(), std::size_t(1));
    ASSERT_EQ(req.body.content, std::string("data"));
}

TESTKIT_MAIN(runner)
