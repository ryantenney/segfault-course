// Exercise 06 -- Tests (read-only)
//
// Verifies fluent Response builder.

#include <testkit/testkit.h>
#include <string>
#include "ex06.h"

static testkit::TestRunner runner("05-49-ex06: Response Builder");

TEST(runner, "build with status only") {
    auto resp = ResponseBuilder().status(200).build();
    ASSERT_EQ(resp.status_code, 200);
}

TEST(runner, "build with status and body") {
    auto resp = ResponseBuilder()
                    .status(200)
                    .set_body("Hello")
                    .build();
    ASSERT_EQ(resp.status_code, 200);
    ASSERT_EQ(resp.body, std::string("Hello"));
}

TEST(runner, "build with headers") {
    auto resp = ResponseBuilder()
                    .status(200)
                    .header("Content-Type", "text/plain")
                    .header("X-Custom", "value")
                    .build();
    ASSERT_EQ(static_cast<int>(resp.headers.size()), 2);
    ASSERT_EQ(resp.headers.at("Content-Type"), std::string("text/plain"));
    ASSERT_EQ(resp.headers.at("X-Custom"), std::string("value"));
}

TEST(runner, "full chain: status + headers + body") {
    auto resp = ResponseBuilder()
                    .status(201)
                    .header("Location", "/items/42")
                    .header("Content-Type", "application/json")
                    .set_body("{\"id\":42}")
                    .build();
    ASSERT_EQ(resp.status_code, 201);
    ASSERT_EQ(resp.body, std::string("{\"id\":42}"));
    ASSERT_EQ(resp.headers.at("Location"), std::string("/items/42"));
}

TEST(runner, "default response has status 0 and empty body") {
    auto resp = ResponseBuilder().build();
    ASSERT_EQ(resp.status_code, 0);
    ASSERT_EQ(resp.body, std::string(""));
    ASSERT_TRUE(resp.headers.empty());
}

TEST(runner, "header overwrites duplicate key") {
    auto resp = ResponseBuilder()
                    .status(200)
                    .header("X-Key", "first")
                    .header("X-Key", "second")
                    .build();
    ASSERT_EQ(resp.headers.at("X-Key"), std::string("second"));
}

TESTKIT_MAIN(runner)
