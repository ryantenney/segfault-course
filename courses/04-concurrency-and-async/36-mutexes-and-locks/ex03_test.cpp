// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. safe_swap exchanges values correctly.
//   2. safe_swap works under concurrent access without deadlock.

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include "ex03.h"

static testkit::TestRunner runner("04-36-ex03: Scoped Lock for Multiple Mutexes");

TEST(runner, "safe_swap exchanges values") {
    LockedBox a(10);
    LockedBox b(20);
    safe_swap(a, b);  // gates on TODO()
    ASSERT_EQ(a.value(), 20);
    ASSERT_EQ(b.value(), 10);
}

TEST(runner, "safe_swap with same box is a no-op (identity)") {
    LockedBox a(42);
    // Swapping with self might deadlock with naive locking.
    // But with scoped_lock, locking the same mutex twice is UB.
    // So we just test two distinct boxes with equal values.
    LockedBox b(42);
    safe_swap(a, b);  // gates on TODO()
    ASSERT_EQ(a.value(), 42);
    ASSERT_EQ(b.value(), 42);
}

TEST(runner, "safe_swap does not deadlock under contention") {
    LockedBox a(1);
    LockedBox b(2);
    safe_swap(a, b);  // gate

    // Reset
    a.value() = 0;
    b.value() = 0;

    // Two threads swap in opposite orders — this would deadlock
    // with naive sequential locking.
    constexpr int iterations = 10000;
    std::thread t1([&] {
        for (int i = 0; i < iterations; ++i) {
            safe_swap(a, b);
        }
    });
    std::thread t2([&] {
        for (int i = 0; i < iterations; ++i) {
            safe_swap(b, a);
        }
    });
    t1.join();
    t2.join();

    // After an even number of swaps from each thread, values should
    // still be 0 and 0 (since we started with equal values).
    int sum = a.value() + b.value();
    ASSERT_EQ(sum, 0);
}

TESTKIT_MAIN(runner)
