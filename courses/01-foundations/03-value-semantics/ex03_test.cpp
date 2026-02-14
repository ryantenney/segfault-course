// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex03.h"

static testkit::TestRunner runner("01-03-ex03: Const-Qualify a Method");

TEST(runner, "get_count returns the current count") {
    Counter c("test", 5);
    ASSERT_EQ(c.get_count(), 5);
    c.increment();
    ASSERT_EQ(c.get_count(), 6);
}

TEST(runner, "get_name returns the name") {
    Counter c("clicks", 0);
    ASSERT_EQ(c.get_name(), std::string("clicks"));
}

TEST(runner, "const Counter can call get_count and get_name") {
    const Counter c("views", 42);
    // These calls only compile if get_count() and get_name() are const
    ASSERT_EQ(c.get_count(), 42);
    ASSERT_EQ(c.get_name(), std::string("views"));
}

TEST(runner, "const reference can call const methods") {
    Counter c("hits", 10);
    const Counter& ref = c;
    ASSERT_EQ(ref.get_count(), 10);
    ASSERT_EQ(ref.get_name(), std::string("hits"));
}

TESTKIT_MAIN(runner)
