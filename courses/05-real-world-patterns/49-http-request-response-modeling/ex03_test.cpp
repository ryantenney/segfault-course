// Exercise 03 -- Tests (read-only)
//
// Verifies case-insensitive header storage and retrieval.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("05-49-ex03: Headers Class");

TEST(runner, "set and get a header") {
    Headers h;
    h.set("Content-Type", "text/html");
    auto val = h.get("Content-Type");
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), std::string("text/html"));
}

TEST(runner, "get returns nullopt for missing key") {
    Headers h;
    auto val = h.get("X-Missing");
    ASSERT_FALSE(val.has_value());
}

TEST(runner, "has returns true for existing key") {
    Headers h;
    h.set("Host", "example.com");
    ASSERT_TRUE(h.has("Host"));
    ASSERT_FALSE(h.has("Accept"));
}

TEST(runner, "case-insensitive lookup") {
    Headers h;
    h.set("Content-Type", "text/html");
    ASSERT_TRUE(h.has("content-type"));
    ASSERT_TRUE(h.has("CONTENT-TYPE"));
    auto val = h.get("content-type");
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), std::string("text/html"));
}

TEST(runner, "set overwrites existing value") {
    Headers h;
    h.set("Accept", "text/plain");
    h.set("accept", "application/json");
    auto val = h.get("Accept");
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), std::string("application/json"));
}

TEST(runner, "remove deletes the header") {
    Headers h;
    h.set("Authorization", "Bearer token");
    ASSERT_TRUE(h.has("Authorization"));
    h.remove("authorization");
    ASSERT_FALSE(h.has("Authorization"));
}

TEST(runner, "remove on missing key is a no-op") {
    Headers h;
    h.remove("X-Nothing");  // should not throw
    ASSERT_FALSE(h.has("X-Nothing"));
}

TESTKIT_MAIN(runner)
