// Exercise 05 -- Tests (read-only)
//
// Verifies Request construction and helper functions.

#include <testkit/testkit.h>
#include <map>
#include <optional>
#include <string>
#include "ex05.h"

static testkit::TestRunner runner("05-49-ex05: Request Type");

TEST(runner, "make_request stores method and path") {
    auto req = make_request("GET", "/api/users", "",
                            {}, std::nullopt);
    ASSERT_EQ(req.method, std::string("GET"));
    ASSERT_EQ(req.path, std::string("/api/users"));
}

TEST(runner, "make_request stores headers") {
    std::map<std::string, std::string> hdrs = {{"Host", "example.com"}};
    auto req = make_request("GET", "/", "", hdrs, std::nullopt);
    ASSERT_EQ(static_cast<int>(req.headers.size()), 1);
    ASSERT_EQ(req.headers.at("Host"), std::string("example.com"));
}

TEST(runner, "make_request stores body") {
    auto req = make_request("POST", "/submit", "",
                            {}, std::string("data"));
    ASSERT_TRUE(req.body.has_value());
    ASSERT_EQ(req.body.value(), std::string("data"));
}

TEST(runner, "make_request with no body") {
    auto req = make_request("GET", "/", "", {}, std::nullopt);
    ASSERT_FALSE(req.body.has_value());
}

TEST(runner, "has_body returns true when body is present and non-empty") {
    auto req = make_request("POST", "/", "", {}, std::string("hello"));
    ASSERT_TRUE(has_body(req));
}

TEST(runner, "has_body returns false when body is nullopt") {
    auto req = make_request("GET", "/", "", {}, std::nullopt);
    ASSERT_FALSE(has_body(req));
}

TEST(runner, "has_body returns false when body is empty string") {
    auto req = make_request("POST", "/", "", {}, std::string(""));
    ASSERT_FALSE(has_body(req));
}

TEST(runner, "full_path without query") {
    auto req = make_request("GET", "/api", "", {}, std::nullopt);
    ASSERT_EQ(full_path(req), std::string("/api"));
}

TEST(runner, "full_path with query") {
    auto req = make_request("GET", "/api", "key=val", {}, std::nullopt);
    ASSERT_EQ(full_path(req), std::string("/api?key=val"));
}

TEST(runner, "make_request stores query string") {
    auto req = make_request("GET", "/search", "q=hello", {}, std::nullopt);
    ASSERT_EQ(req.query, std::string("q=hello"));
}

TESTKIT_MAIN(runner)
