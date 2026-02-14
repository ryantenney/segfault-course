// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <atomic>
#include <thread>
#include <vector>

#include "ex06.h"

static testkit::TestRunner runner("04-37-ex06: notify_one vs notify_all");

TEST(runner, "barrier of 1 does not block") {
    Barrier b(1);
    b.arrive_and_wait();  // gates on TODO(), also should not block
    ASSERT_EQ(b.arrived(), std::size_t(1));
}

TEST(runner, "arrive increments the count") {
    // With a barrier of 1, arrive_and_wait should complete immediately
    Barrier b(1);
    b.arrive_and_wait();
    ASSERT_EQ(b.arrived(), std::size_t(1));
}

TEST(runner, "all threads pass through the barrier") {
    // Gate: verify single-thread case works
    {
        Barrier gate(1);
        gate.arrive_and_wait();
    }

    constexpr std::size_t N = 4;
    Barrier b(N);
    std::atomic<int> count{0};
    std::vector<std::thread> threads;

    for (std::size_t i = 0; i < N; ++i) {
        threads.emplace_back([&] {
            b.arrive_and_wait();
            count.fetch_add(1);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    ASSERT_EQ(count.load(), static_cast<int>(N));
    ASSERT_EQ(b.arrived(), N);
}

TEST(runner, "barrier releases all threads simultaneously") {
    // Gate
    {
        Barrier gate(1);
        gate.arrive_and_wait();
    }

    constexpr std::size_t N = 3;
    Barrier b(N);
    std::atomic<int> after_barrier{0};

    // Launch N-1 threads that will block at the barrier
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < N - 1; ++i) {
        threads.emplace_back([&] {
            b.arrive_and_wait();
            after_barrier.fetch_add(1);
        });
    }

    // Give threads time to reach the barrier
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // None should have passed the barrier yet
    ASSERT_EQ(after_barrier.load(), 0);

    // Last thread arrives -- should release everyone
    b.arrive_and_wait();
    for (auto& t : threads) {
        t.join();
    }

    ASSERT_EQ(after_barrier.load(), static_cast<int>(N - 1));
}

TESTKIT_MAIN(runner)
