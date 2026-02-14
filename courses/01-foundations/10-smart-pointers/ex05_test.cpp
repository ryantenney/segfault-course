// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-10-ex05: Shared Ownership");

TEST(runner, "open_connection creates a shared_ptr with ref count 1") {
    auto conn = open_connection("localhost:8080");
    ASSERT_TRUE(conn != nullptr);
    ASSERT_EQ(conn->endpoint, std::string("localhost:8080"));
    ASSERT_EQ(get_ref_count(conn), 1L);
}

TEST(runner, "share_connection increases reference count") {
    auto conn = open_connection("db:5432");
    auto copy = share_connection(conn);
    ASSERT_EQ(get_ref_count(conn), 2L);
    ASSERT_EQ(get_ref_count(copy), 2L);
    ASSERT_EQ(conn->endpoint, copy->endpoint);
}

TEST(runner, "multiple shares increase count correctly") {
    auto c1 = open_connection("redis:6379");
    auto c2 = share_connection(c1);
    auto c3 = share_connection(c1);
    ASSERT_EQ(get_ref_count(c1), 3L);
}

TEST(runner, "close_and_report resets one owner and reports remaining count") {
    auto conn = open_connection("api:443");
    auto observer = share_connection(conn);
    ASSERT_EQ(get_ref_count(conn), 2L);

    long remaining = close_and_report(conn, observer);
    ASSERT_TRUE(conn == nullptr);
    ASSERT_EQ(remaining, 1L);
}

TESTKIT_MAIN(runner)
