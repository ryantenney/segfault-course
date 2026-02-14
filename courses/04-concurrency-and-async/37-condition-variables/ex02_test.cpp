// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>

#include "ex02.h"

static testkit::TestRunner runner("04-37-ex02: Predicate Wait");

TEST(runner, "initial value is zero") {
    PredicateNotifier pn;
    // Gate on set_value
    pn.set_value(0);
    PredicateNotifier fresh;
    ASSERT_EQ(fresh.get_value(), 0);
}

TEST(runner, "set_value updates the stored value") {
    PredicateNotifier pn;
    pn.set_value(42);
    ASSERT_EQ(pn.get_value(), 42);
}

TEST(runner, "wait_for_value returns immediately if value already matches") {
    PredicateNotifier pn;
    pn.set_value(10);
    pn.wait_for_value(10);
    ASSERT_EQ(pn.get_value(), 10);
}

TEST(runner, "wait_for_value blocks until value matches") {
    PredicateNotifier pn;
    // Gate: ensure set_value works
    pn.set_value(0);

    std::thread t([&pn] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        pn.set_value(99);
    });

    pn.wait_for_value(99);
    ASSERT_EQ(pn.get_value(), 99);
    t.join();
}

TEST(runner, "wait_for_value ignores non-matching updates") {
    PredicateNotifier pn;
    // Gate
    pn.set_value(0);

    std::thread t([&pn] {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        pn.set_value(1);  // not the target
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        pn.set_value(2);  // not the target
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        pn.set_value(3);  // this is the target
    });

    pn.wait_for_value(3);
    ASSERT_EQ(pn.get_value(), 3);
    t.join();
}

TESTKIT_MAIN(runner)
