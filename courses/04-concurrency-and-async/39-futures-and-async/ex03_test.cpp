// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. send_value sets the value on the promise.
//   2. The corresponding future receives the value.
//   3. Works from a different thread.

#include <testkit/testkit.h>
#include <future>
#include <thread>
#include "ex03.h"

static testkit::TestRunner runner("04-39-ex03: Promise-Future Channel");

TEST(runner, "send_value sets value on promise") {
    std::promise<int> p;
    auto f = p.get_future();
    send_value(p, 42);
    ASSERT_EQ(f.get(), 42);
}

TEST(runner, "send_value with negative value") {
    std::promise<int> p;
    auto f = p.get_future();
    send_value(p, -7);
    ASSERT_EQ(f.get(), -7);
}

TEST(runner, "send_value with zero") {
    std::promise<int> p;
    auto f = p.get_future();
    send_value(p, 0);
    ASSERT_EQ(f.get(), 0);
}

TEST(runner, "send_value works from a thread") {
    // Gate: call directly first to ensure it doesn't throw not_implemented.
    {
        std::promise<int> gate_p;
        send_value(gate_p, 1);
    }

    std::promise<int> p;
    auto f = p.get_future();
    std::thread t([&p] { send_value(p, 99); });
    ASSERT_EQ(f.get(), 99);
    t.join();
}

TESTKIT_MAIN(runner)
