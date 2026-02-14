// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. get_call_count returns incrementing values per thread.
//   2. Each thread has its own independent counter.

#include <testkit/testkit.h>
#include <thread>
#include "ex07.h"

static testkit::TestRunner runner("04-35-ex07: Thread-local Storage");

TEST(runner, "get_call_count returns incrementing values") {
    // Gate: call on main thread first to check if implemented.
    // This call also increments the main thread's counter, but
    // we test in fresh threads below for clean counters.
    get_call_count();  // gates on TODO() via ex07_gate()

    int r1 = 0, r2 = 0, r3 = 0;
    std::thread t([&] {
        r1 = get_call_count();
        r2 = get_call_count();
        r3 = get_call_count();
    });
    t.join();
    ASSERT_EQ(r1, 1);
    ASSERT_EQ(r2, 2);
    ASSERT_EQ(r3, 3);
}

TEST(runner, "each thread has independent counter") {
    get_call_count();  // gate on main thread

    int thread_a_result = 0;
    int thread_b_result = 0;

    std::thread ta([&] {
        get_call_count();
        get_call_count();
        thread_a_result = get_call_count();  // should be 3
    });
    ta.join();

    std::thread tb([&] {
        thread_b_result = get_call_count();  // should be 1 (fresh thread)
    });
    tb.join();

    ASSERT_EQ(thread_a_result, 3);
    ASSERT_EQ(thread_b_result, 1);
}

TESTKIT_MAIN(runner)
