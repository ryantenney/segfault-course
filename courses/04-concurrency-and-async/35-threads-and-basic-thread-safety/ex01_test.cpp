// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. compute_answer sets result to 42.
//   2. compute_answer works correctly when called from a thread.

#include <testkit/testkit.h>
#include <thread>
#include "ex01.h"

static testkit::TestRunner runner("04-35-ex01: Launch and Join");

TEST(runner, "compute_answer sets result to 42") {
    int result = 0;
    compute_answer(result);  // gates on TODO() — skips before threads
    ASSERT_EQ(result, 42);
}

TEST(runner, "compute_answer works from a thread") {
    int result = 0;
    compute_answer(result);  // gate: hits TODO() and skips if not implemented
    result = 0;              // reset for the real test

    std::thread t([&result] { compute_answer(result); });
    t.join();
    ASSERT_EQ(result, 42);
}

TEST(runner, "thread id differs from main thread") {
    int result = 0;
    compute_answer(result);  // gate

    std::thread::id main_id = std::this_thread::get_id();
    std::thread::id worker_id;
    std::thread t([&worker_id, &result] {
        worker_id = std::this_thread::get_id();
        compute_answer(result);
    });
    t.join();
    ASSERT_NE(main_id, worker_id);
}

TESTKIT_MAIN(runner)
