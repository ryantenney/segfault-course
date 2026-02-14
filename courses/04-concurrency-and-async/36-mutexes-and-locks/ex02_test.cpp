// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. transfer moves money correctly.
//   2. transfer rejects insufficient funds.

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("04-36-ex02: lock_guard Scope");

TEST(runner, "transfer moves amount from one account to another") {
    GuardedAccount a(100);
    GuardedAccount b(50);
    bool ok = transfer(a, b, 30);  // gates on TODO()
    ASSERT_TRUE(ok);
    ASSERT_EQ(a.balance(), 70);
    ASSERT_EQ(b.balance(), 80);
}

TEST(runner, "transfer rejects insufficient funds") {
    GuardedAccount a(10);
    GuardedAccount b(50);
    bool ok = transfer(a, b, 30);  // gates on TODO()
    ASSERT_FALSE(ok);
    ASSERT_EQ(a.balance(), 10);
    ASSERT_EQ(b.balance(), 50);
}

TEST(runner, "transfer of zero is allowed") {
    GuardedAccount a(100);
    GuardedAccount b(100);
    bool ok = transfer(a, b, 0);  // gates on TODO()
    ASSERT_TRUE(ok);
    ASSERT_EQ(a.balance(), 100);
    ASSERT_EQ(b.balance(), 100);
}

TEST(runner, "multiple transfers accumulate correctly") {
    GuardedAccount a(100);
    GuardedAccount b(0);
    transfer(a, b, 25);  // gate
    transfer(a, b, 25);
    transfer(a, b, 25);
    ASSERT_EQ(a.balance(), 25);
    ASSERT_EQ(b.balance(), 75);
}

TESTKIT_MAIN(runner)
