// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex04.h"

static testkit::TestRunner runner("04-38-ex04: Compare-and-Swap");

TEST(runner, "atomic_max updates when value is greater") {
    std::atomic<int> a{5};
    atomic_max(a, 10);
    ASSERT_EQ(a.load(), 10);
}

TEST(runner, "atomic_max does nothing when value is smaller") {
    std::atomic<int> a{10};
    atomic_max(a, 5);
    ASSERT_EQ(a.load(), 10);
}

TEST(runner, "atomic_max does nothing when value is equal") {
    std::atomic<int> a{7};
    atomic_max(a, 7);
    ASSERT_EQ(a.load(), 7);
}

TEST(runner, "atomic_max works with negative numbers") {
    std::atomic<int> a{-5};
    atomic_max(a, -3);
    ASSERT_EQ(a.load(), -3);
    atomic_max(a, -10);
    ASSERT_EQ(a.load(), -3);
}

TEST(runner, "atomic_push adds one element") {
    AtomicStack stack;
    atomic_push(stack, 42);
    ASSERT_TRUE(stack.head.load() != nullptr);
    ASSERT_EQ(atomic_pop(stack), 42);
    ASSERT_TRUE(stack.head.load() == nullptr);
}

TEST(runner, "atomic_push maintains LIFO order") {
    AtomicStack stack;
    atomic_push(stack, 1);
    atomic_push(stack, 2);
    atomic_push(stack, 3);
    // LIFO: should come back as 3, 2, 1
    ASSERT_EQ(atomic_pop(stack), 3);
    ASSERT_EQ(atomic_pop(stack), 2);
    ASSERT_EQ(atomic_pop(stack), 1);
}

TEST(runner, "concurrent atomic_max finds the true maximum") {
    std::atomic<int> a{0};
    // Gate: ensure single-threaded works
    atomic_max(a, 0);

    std::vector<std::thread> tv;
    for (int i = 1; i <= 100; ++i) {
        tv.emplace_back([&a, i] {
            atomic_max(a, i);
        });
    }
    for (auto& t : tv) {
        t.join();
    }
    ASSERT_EQ(a.load(), 100);
}

TEST(runner, "concurrent atomic_push preserves all elements") {
    AtomicStack stack;
    // Gate: verify single-threaded push works
    atomic_push(stack, 0);
    atomic_pop(stack);

    constexpr int N = 100;
    std::vector<std::thread> tv;
    for (int i = 0; i < N; ++i) {
        tv.emplace_back([&stack, i] {
            atomic_push(stack, i);
        });
    }
    for (auto& t : tv) {
        t.join();
    }

    // Pop all elements and sum them
    int sum = 0;
    int count = 0;
    while (stack.head.load() != nullptr) {
        sum += atomic_pop(stack);
        ++count;
    }
    ASSERT_EQ(count, N);
    ASSERT_EQ(sum, N * (N - 1) / 2);
}

TESTKIT_MAIN(runner)
