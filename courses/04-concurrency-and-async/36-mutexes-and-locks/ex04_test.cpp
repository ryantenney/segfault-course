// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. try_process returns an element when the queue is non-empty.
//   2. try_process returns -1 on an empty queue.
//   3. try_process returns -1 when the lock is held by another thread.

#include <testkit/testkit.h>
#include <thread>
#include <chrono>
#include "ex04.h"

static testkit::TestRunner runner("04-36-ex04: unique_lock Flexibility");

TEST(runner, "try_process returns front element") {
    SharedQueue q;
    q.push(10);
    q.push(20);
    int result = try_process(q);  // gates on TODO()
    ASSERT_EQ(result, 10);
}

TEST(runner, "try_process removes the element") {
    SharedQueue q;
    q.push(10);
    q.push(20);
    try_process(q);  // gates on TODO()
    int result = try_process(q);
    ASSERT_EQ(result, 20);
}

TEST(runner, "try_process returns -1 on empty queue") {
    SharedQueue q;
    int result = try_process(q);  // gates on TODO()
    ASSERT_EQ(result, -1);
}

TEST(runner, "try_process returns -1 when lock is held") {
    SharedQueue q;
    q.push(42);
    try_process(q);  // gate — make sure it's implemented
    q.push(42);      // re-add element

    // Hold the lock from the main thread
    std::lock_guard<std::mutex> held(q.mutex());

    // try_process from another thread should fail to lock
    int result = -99;
    std::thread t([&q, &result] {
        result = try_process(q);
    });
    t.join();
    ASSERT_EQ(result, -1);
}

TESTKIT_MAIN(runner)
