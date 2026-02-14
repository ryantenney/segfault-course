// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. add_to modifies the target correctly.
//   2. add_to works from a thread with std::ref.

#include <testkit/testkit.h>
#include <thread>
#include "ex02.h"

static testkit::TestRunner runner("04-35-ex02: Thread with Arguments");

TEST(runner, "add_to adds amount to target") {
    int target = 10;
    add_to(target, 5);  // gates on TODO()
    ASSERT_EQ(target, 15);
}

TEST(runner, "add_to with negative amount") {
    int target = 10;
    add_to(target, -3);  // gates on TODO()
    ASSERT_EQ(target, 7);
}

TEST(runner, "add_to works from a thread with std::ref") {
    int target = 0;
    add_to(target, 1);  // gate
    target = 0;          // reset

    std::thread t(add_to, std::ref(target), 100);
    t.join();
    ASSERT_EQ(target, 100);
}

TEST(runner, "multiple threads each add to target") {
    int target = 0;
    add_to(target, 1);  // gate
    target = 0;          // reset

    std::thread t1(add_to, std::ref(target), 10);
    t1.join();
    std::thread t2(add_to, std::ref(target), 20);
    t2.join();
    ASSERT_EQ(target, 30);
}

TESTKIT_MAIN(runner)
