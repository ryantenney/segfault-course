// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. safe_transfer moves money correctly.
//   2. safe_transfer doesn't deadlock under concurrent opposing transfers.

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include "ex07.h"

static testkit::TestRunner runner("04-36-ex07: Deadlock Identification");

TEST(runner, "safe_transfer moves money correctly") {
    Account a(100);
    Account b(50);
    bool ok = safe_transfer(a, b, 30);  // gates on TODO()
    ASSERT_TRUE(ok);
    ASSERT_EQ(a.balance(), 70);
    ASSERT_EQ(b.balance(), 80);
}

TEST(runner, "safe_transfer rejects insufficient funds") {
    Account a(10);
    Account b(50);
    bool ok = safe_transfer(a, b, 30);  // gates on TODO()
    ASSERT_FALSE(ok);
    ASSERT_EQ(a.balance(), 10);
    ASSERT_EQ(b.balance(), 50);
}

TEST(runner, "safe_transfer preserves total balance") {
    Account a(100);
    Account b(100);
    safe_transfer(a, b, 30);  // gate
    ASSERT_EQ(a.balance() + b.balance(), 200);
}

TEST(runner, "safe_transfer does not deadlock with opposing transfers") {
    Account a(100000);
    Account b(100000);
    safe_transfer(a, b, 1);  // gate

    // Reset
    Account x(100000);
    Account y(100000);

    constexpr int iterations = 5000;

    // Two threads transferring in opposite directions — this would
    // deadlock with broken_transfer.
    std::thread t1([&] {
        for (int i = 0; i < iterations; ++i) {
            safe_transfer(x, y, 1);
        }
    });
    std::thread t2([&] {
        for (int i = 0; i < iterations; ++i) {
            safe_transfer(y, x, 1);
        }
    });
    t1.join();
    t2.join();

    // Total should be preserved
    ASSERT_EQ(x.balance() + y.balance(), 200000);
}

TESTKIT_MAIN(runner)
