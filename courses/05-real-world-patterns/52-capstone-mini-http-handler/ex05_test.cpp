// Exercise 05 -- Tests (read-only)
//
// Verifies parsing of raw HTTP-like strings into Request structs.

#include <testkit/testkit.h>
#include "ex05.h"

#include <string>

static testkit::TestRunner runner("05-52-ex05: Request Parsing");

TEST(runner, "parse simple GET request") {
    std::string raw = "GET /hello HTTP/1.1\r\n\r\n";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string("GET"));
    ASSERT_EQ(req.path, std::string("/hello"));
    ASSERT_EQ(req.version, std::string("HTTP/1.1"));
    ASSERT_EQ(req.body, std::string(""));
}

TEST(runner, "parse request with headers") {
    std::string raw = "GET /api HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "Accept: text/plain\r\n"
                      "\r\n";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string("GET"));
    ASSERT_EQ(req.path, std::string("/api"));
    ASSERT_EQ(req.headers.size(), size_t(2));
    ASSERT_EQ(req.headers.at("Host"), std::string("example.com"));
    ASSERT_EQ(req.headers.at("Accept"), std::string("text/plain"));
}

TEST(runner, "parse POST request with body") {
    std::string raw = "POST /data HTTP/1.1\r\n"
                      "Content-Type: application/json\r\n"
                      "\r\n"
                      "{\"key\":\"value\"}";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string("POST"));
    ASSERT_EQ(req.path, std::string("/data"));
    ASSERT_EQ(req.headers.at("Content-Type"), std::string("application/json"));
    ASSERT_EQ(req.body, std::string("{\"key\":\"value\"}"));
}

TEST(runner, "parse request with multi-line body") {
    std::string raw = "POST /submit HTTP/1.1\r\n"
                      "\r\n"
                      "line1\r\nline2";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string("POST"));
    ASSERT_EQ(req.body, std::string("line1\r\nline2"));
}

TEST(runner, "parse failure returns empty method") {
    std::string raw = "";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string(""));
}

TEST(runner, "parse incomplete request line returns empty method") {
    std::string raw = "GET\r\n\r\n";
    Request req = parse_request(raw);
    ASSERT_EQ(req.method, std::string(""));
}

TESTKIT_MAIN(runner)
