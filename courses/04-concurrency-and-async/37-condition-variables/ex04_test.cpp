// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <thread>

#include "ex04.h"

static testkit::TestRunner runner("04-37-ex04: Work Queue");

TEST(runner, "push and pop a single item") {
    WorkQueue<int> wq;
    wq.push(42);
    auto val = wq.pop();
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), 42);
}

TEST(runner, "pop returns items in FIFO order") {
    WorkQueue<std::string> wq;
    wq.push("alpha");
    wq.push("beta");
    wq.push("gamma");
    auto v1 = wq.pop();
    auto v2 = wq.pop();
    auto v3 = wq.pop();
    ASSERT_EQ(v1.value(), std::string("alpha"));
    ASSERT_EQ(v2.value(), std::string("beta"));
    ASSERT_EQ(v3.value(), std::string("gamma"));
}

TEST(runner, "is_shutdown returns false initially") {
    WorkQueue<int> wq;
    // Gate: push to verify it works
    wq.push(0);
    wq.pop();
    ASSERT_FALSE(wq.is_shutdown());
}

TEST(runner, "shutdown sets the shutdown flag") {
    WorkQueue<int> wq;
    wq.shutdown();
    ASSERT_TRUE(wq.is_shutdown());
}

TEST(runner, "pop returns nullopt after shutdown on empty queue") {
    WorkQueue<int> wq;
    wq.shutdown();
    auto val = wq.pop();
    ASSERT_FALSE(val.has_value());
}

TEST(runner, "pop drains remaining items after shutdown") {
    WorkQueue<int> wq;
    wq.push(1);
    wq.push(2);
    wq.shutdown();
    auto a = wq.pop();
    auto b = wq.pop();
    auto c = wq.pop();
    ASSERT_EQ(a.value(), 1);
    ASSERT_EQ(b.value(), 2);
    ASSERT_FALSE(c.has_value());
}

TEST(runner, "pop blocks until item is pushed from another thread") {
    WorkQueue<int> wq;
    // Gate: ensure push/pop works
    wq.push(0);
    wq.pop();

    std::thread producer([&wq] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        wq.push(77);
    });

    auto val = wq.pop();  // blocks until producer pushes
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), 77);
    producer.join();
}

TEST(runner, "pop unblocks on shutdown") {
    WorkQueue<int> wq;
    // Gate
    wq.push(0);
    wq.pop();

    std::thread stopper([&wq] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        wq.shutdown();
    });

    auto val = wq.pop();  // blocks until shutdown
    ASSERT_FALSE(val.has_value());
    stopper.join();
}

TESTKIT_MAIN(runner)
