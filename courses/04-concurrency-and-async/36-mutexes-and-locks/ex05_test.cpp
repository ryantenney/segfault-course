// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. try_lock_for_ms acquires an uncontested lock.
//   2. try_lock_for_ms times out when the lock is held.

#include <testkit/testkit.h>
#include <thread>
#include <chrono>
#include "ex05.h"

static testkit::TestRunner runner("04-36-ex05: Timed Lock");

TEST(runner, "acquires uncontested lock and sets value") {
    TimedMutexWrapper w;
    bool ok = try_lock_for_ms(w, 100);  // gates on TODO()
    ASSERT_TRUE(ok);
    ASSERT_EQ(w.value(), 1);
}

TEST(runner, "times out when lock is already held") {
    TimedMutexWrapper w;
    try_lock_for_ms(w, 100);  // gate
    w.set_value(0);           // reset

    // Hold the lock from main thread
    w.mutex().lock();

    bool result = false;
    std::thread t([&w, &result] {
        result = try_lock_for_ms(w, 10);  // short timeout
    });
    t.join();

    w.mutex().unlock();

    ASSERT_FALSE(result);
    ASSERT_EQ(w.value(), 0);  // value should not have changed
}

TEST(runner, "succeeds after lock is released within timeout") {
    TimedMutexWrapper w;
    try_lock_for_ms(w, 100);  // gate
    w.set_value(0);           // reset

    w.mutex().lock();

    bool result = false;
    std::thread t([&w, &result] {
        result = try_lock_for_ms(w, 500);  // long timeout
    });

    // Release the lock after a short delay
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    w.mutex().unlock();

    t.join();
    ASSERT_TRUE(result);
    ASSERT_EQ(w.value(), 1);
}

TESTKIT_MAIN(runner)
