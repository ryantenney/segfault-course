// Exercise 08 — Tests (read-only)
//
// These tests verify that:
//   1. Synchronized<T>::apply works for reads and writes.
//   2. The wrapper is thread-safe.

#include <testkit/testkit.h>
#include <string>
#include <thread>
#include <vector>
#include "ex08.h"

static testkit::TestRunner runner("04-36-ex08: Thread-safe Wrapper");

TEST(runner, "apply reads the value") {
    Synchronized<int> s(42);
    int result = s.apply([](int& v) { return v; });  // gates on TODO()
    ASSERT_EQ(result, 42);
}

TEST(runner, "apply modifies the value") {
    Synchronized<int> s(0);
    s.apply([](int& v) { v = 99; });  // gates on TODO()
    int result = s.apply([](int& v) { return v; });
    ASSERT_EQ(result, 99);
}

TEST(runner, "const apply reads without modification") {
    const Synchronized<std::string> s("hello");
    std::string result = s.apply([](const std::string& v) { return v; });
    // gates on TODO() in const apply
    ASSERT_EQ(result, "hello");
}

TEST(runner, "apply works with string operations") {
    Synchronized<std::string> s("hello");
    s.apply([](std::string& v) { v += " world"; });  // gates on TODO()
    std::string result = s.apply([](std::string& v) { return v; });
    ASSERT_EQ(result, "hello world");
}

TEST(runner, "apply with void return") {
    Synchronized<int> s(0);
    s.apply([](int& v) { v = 42; });  // gates on TODO()
    int result = s.apply([](int& v) { return v; });
    ASSERT_EQ(result, 42);
}

TEST(runner, "thread-safe under concurrent access") {
    Synchronized<int> s(0);
    s.apply([](int& v) { v = 0; });  // gate

    Synchronized<int> counter(0);
    constexpr int num_threads = 8;
    constexpr int increments_per_thread = 10000;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter] {
            for (int j = 0; j < increments_per_thread; ++j) {
                counter.apply([](int& v) { ++v; });
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    int result = counter.apply([](int& v) { return v; });
    ASSERT_EQ(result, num_threads * increments_per_thread);
}

TESTKIT_MAIN(runner)
