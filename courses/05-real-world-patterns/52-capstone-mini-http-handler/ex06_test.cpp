// Exercise 06 -- Tests (read-only)
//
// Verifies Response serialization to HTTP-like string format.

#include <testkit/testkit.h>
#include "ex06.h"

#include <string>

static testkit::TestRunner runner("05-52-ex06: Response Serialization");

TEST(runner, "reason_phrase for 200") {
    ASSERT_EQ(reason_phrase(200), std::string("OK"));
}

TEST(runner, "reason_phrase for 404") {
    ASSERT_EQ(reason_phrase(404), std::string("Not Found"));
}

TEST(runner, "reason_phrase for 500") {
    ASSERT_EQ(reason_phrase(500), std::string("Internal Server Error"));
}

TEST(runner, "reason_phrase for unknown status") {
    ASSERT_EQ(reason_phrase(418), std::string("Unknown"));
}

TEST(runner, "serialize simple 200 response") {
    Response resp{200, {}, "Hello"};
    std::string raw = serialize_response(resp);
    std::string expected = "HTTP/1.1 200 OK\r\n\r\nHello";
    ASSERT_EQ(raw, expected);
}

TEST(runner, "serialize response with headers") {
    Response resp;
    resp.status = 200;
    resp.headers["Content-Type"] = "text/plain";
    resp.body = "hi";
    std::string raw = serialize_response(resp);
    // Must contain status line
    ASSERT_TRUE(raw.find("HTTP/1.1 200 OK\r\n") == 0);
    // Must contain header
    ASSERT_TRUE(raw.find("Content-Type: text/plain\r\n") != std::string::npos);
    // Must end with body after blank line
    ASSERT_TRUE(raw.find("\r\n\r\nhi") != std::string::npos);
}

TEST(runner, "serialize 404 response") {
    Response resp{404, {}, "Not Found"};
    std::string raw = serialize_response(resp);
    ASSERT_TRUE(raw.find("HTTP/1.1 404 Not Found\r\n") == 0);
    ASSERT_TRUE(raw.find("\r\n\r\nNot Found") != std::string::npos);
}

TEST(runner, "serialize response with empty body") {
    Response resp{204, {}, ""};
    std::string raw = serialize_response(resp);
    ASSERT_TRUE(raw.find("HTTP/1.1 204 Unknown\r\n") == 0);
    ASSERT_TRUE(raw.find("\r\n\r\n") != std::string::npos);
}

TESTKIT_MAIN(runner)
