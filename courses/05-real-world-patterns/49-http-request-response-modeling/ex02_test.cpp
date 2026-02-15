// Exercise 02 -- Tests (read-only)
//
// Verifies status code category helpers and reason phrases.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("05-49-ex02: Status Code Enum");

TEST(runner, "200 is success") {
    ASSERT_TRUE(is_success(StatusCode(200)));
}

TEST(runner, "201 and 204 are success") {
    ASSERT_TRUE(is_success(StatusCode(201)));
    ASSERT_TRUE(is_success(StatusCode(204)));
}

TEST(runner, "301 is redirect") {
    ASSERT_TRUE(is_redirect(StatusCode(301)));
    ASSERT_FALSE(is_success(StatusCode(301)));
}

TEST(runner, "302 and 304 are redirects") {
    ASSERT_TRUE(is_redirect(StatusCode(302)));
    ASSERT_TRUE(is_redirect(StatusCode(304)));
}

TEST(runner, "400 is client error") {
    ASSERT_TRUE(is_client_error(StatusCode(400)));
    ASSERT_FALSE(is_success(StatusCode(400)));
    ASSERT_FALSE(is_server_error(StatusCode(400)));
}

TEST(runner, "404 and 401 are client errors") {
    ASSERT_TRUE(is_client_error(StatusCode(404)));
    ASSERT_TRUE(is_client_error(StatusCode(401)));
}

TEST(runner, "500 is server error") {
    ASSERT_TRUE(is_server_error(StatusCode(500)));
    ASSERT_FALSE(is_client_error(StatusCode(500)));
}

TEST(runner, "502 and 503 are server errors") {
    ASSERT_TRUE(is_server_error(StatusCode(502)));
    ASSERT_TRUE(is_server_error(StatusCode(503)));
}

TEST(runner, "categories are mutually exclusive") {
    ASSERT_FALSE(is_redirect(StatusCode(200)));
    ASSERT_FALSE(is_client_error(StatusCode(200)));
    ASSERT_FALSE(is_server_error(StatusCode(200)));
}

TEST(runner, "reason_phrase for common codes") {
    ASSERT_EQ(reason_phrase(StatusCode(200)), std::string("OK"));
    ASSERT_EQ(reason_phrase(StatusCode(404)), std::string("Not Found"));
    ASSERT_EQ(reason_phrase(StatusCode(500)), std::string("Internal Server Error"));
}

TEST(runner, "reason_phrase for unknown code") {
    ASSERT_EQ(reason_phrase(StatusCode(999)), std::string("Unknown"));
}

TESTKIT_MAIN(runner)
