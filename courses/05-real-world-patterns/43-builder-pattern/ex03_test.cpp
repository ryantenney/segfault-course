// Exercise 03 -- Tests (read-only)
//
// Verifies that build() produces a Request struct with the correct fields.

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("05-43-ex03: Build Method");

TEST(runner, "build produces Request with all fields") {
    RequestBuilder b;
    Request r = b.set_method("POST")
                 .set_url("https://example.com")
                 .set_body("{\"ok\":true}")
                 .build();
    ASSERT_EQ(r.method, std::string("POST"));
    ASSERT_EQ(r.url, std::string("https://example.com"));
    ASSERT_EQ(r.body, std::string("{\"ok\":true}"));
}

TEST(runner, "build with empty body") {
    RequestBuilder b;
    Request r = b.set_method("GET").set_url("/health").build();
    ASSERT_EQ(r.method, std::string("GET"));
    ASSERT_EQ(r.url, std::string("/health"));
    ASSERT_EQ(r.body, std::string(""));
}

TEST(runner, "builder can be reused after build") {
    RequestBuilder b;
    b.set_method("GET").set_url("/first");
    Request r1 = b.build();

    b.set_url("/second");
    Request r2 = b.build();

    ASSERT_EQ(r1.url, std::string("/first"));
    ASSERT_EQ(r2.url, std::string("/second"));
    ASSERT_EQ(r2.method, std::string("GET"));
}

TEST(runner, "build with all defaults produces empty request") {
    RequestBuilder b;
    Request r = b.build();
    ASSERT_EQ(r.method, std::string(""));
    ASSERT_EQ(r.url, std::string(""));
    ASSERT_EQ(r.body, std::string(""));
}

TEST(runner, "build does not modify builder state") {
    RequestBuilder b;
    b.set_method("PUT").set_url("/data").set_body("payload");
    Request r1 = b.build();
    Request r2 = b.build();
    ASSERT_EQ(r1.method, r2.method);
    ASSERT_EQ(r1.url, r2.url);
    ASSERT_EQ(r1.body, r2.body);
}

TESTKIT_MAIN(runner)
