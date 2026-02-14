// Exercise 02 — Tests (read-only)
//
// Verifies in-class member initializers (NSDMIs) on the Config class.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("03-25-ex02: In-Class Member Initializers");

TEST(runner, "default constructor uses NSDMI defaults") {
    Config c;
    ASSERT_EQ(c.get_max_retries(), 3);
    ASSERT_EQ(c.get_timeout_ms(), 5000);
    ASSERT_FALSE(c.get_verbose());
    ASSERT_EQ(c.get_endpoint(), std::string("http://localhost:8080"));
}

TEST(runner, "two-arg constructor overrides retries and timeout") {
    Config c(5, 10000);
    ASSERT_EQ(c.get_max_retries(), 5);
    ASSERT_EQ(c.get_timeout_ms(), 10000);
}

TEST(runner, "two-arg constructor keeps verbose and endpoint defaults") {
    Config c(5, 10000);
    ASSERT_FALSE(c.get_verbose());
    ASSERT_EQ(c.get_endpoint(), std::string("http://localhost:8080"));
}

TEST(runner, "full constructor overrides all values") {
    Config c(10, 30000, true, "https://api.example.com");
    ASSERT_EQ(c.get_max_retries(), 10);
    ASSERT_EQ(c.get_timeout_ms(), 30000);
    ASSERT_TRUE(c.get_verbose());
    ASSERT_EQ(c.get_endpoint(), std::string("https://api.example.com"));
}

TEST(runner, "multiple default-constructed configs are independent") {
    Config a;
    Config b;
    ASSERT_EQ(a.get_max_retries(), b.get_max_retries());
    ASSERT_EQ(a.get_timeout_ms(), b.get_timeout_ms());
}

TESTKIT_MAIN(runner)
