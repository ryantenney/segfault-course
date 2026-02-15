// Exercise 04 -- Tests (read-only)
//
// Verifies multi-value header support.

#include <testkit/testkit.h>
#include <string>
#include <vector>
#include "ex04.h"

static testkit::TestRunner runner("05-49-ex04: Multi-value Headers");

TEST(runner, "add and get_all for single value") {
    MultiHeaders h;
    h.add("Accept", "text/html");
    auto vals = h.get_all("Accept");
    ASSERT_EQ(static_cast<int>(vals.size()), 1);
    ASSERT_EQ(vals[0], std::string("text/html"));
}

TEST(runner, "add multiple values for same key") {
    MultiHeaders h;
    h.add("Set-Cookie", "a=1");
    h.add("Set-Cookie", "b=2");
    h.add("set-cookie", "c=3");
    auto vals = h.get_all("SET-COOKIE");
    ASSERT_EQ(static_cast<int>(vals.size()), 3);
    ASSERT_EQ(vals[0], std::string("a=1"));
    ASSERT_EQ(vals[1], std::string("b=2"));
    ASSERT_EQ(vals[2], std::string("c=3"));
}

TEST(runner, "get_all returns empty vector for missing key") {
    MultiHeaders h;
    auto vals = h.get_all("X-Missing");
    ASSERT_EQ(static_cast<int>(vals.size()), 0);
}

TEST(runner, "get_first returns first value") {
    MultiHeaders h;
    h.add("Accept", "text/html");
    h.add("Accept", "application/json");
    auto first = h.get_first("Accept");
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(first.value(), std::string("text/html"));
}

TEST(runner, "get_first returns nullopt for missing key") {
    MultiHeaders h;
    ASSERT_FALSE(h.get_first("X-Missing").has_value());
}

TEST(runner, "remove deletes all values") {
    MultiHeaders h;
    h.add("Accept", "text/html");
    h.add("Accept", "application/json");
    h.remove("accept");
    ASSERT_EQ(static_cast<int>(h.get_all("Accept").size()), 0);
    ASSERT_FALSE(h.get_first("Accept").has_value());
}

TESTKIT_MAIN(runner)
