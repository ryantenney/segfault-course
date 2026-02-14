// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>

#include "ex02.h"

static testkit::TestRunner runner("04-38-ex02: Atomic Load/Store");

TEST(runner, "flag starts as false") {
    AtomicFlag f;
    bool val = f.is_set();
    ASSERT_FALSE(val);
}

TEST(runner, "set makes the flag true") {
    AtomicFlag f;
    f.set();
    ASSERT_TRUE(f.is_set());
}

TEST(runner, "clear makes the flag false") {
    AtomicFlag f;
    f.set();
    f.clear();
    ASSERT_FALSE(f.is_set());
}

TEST(runner, "set is idempotent") {
    AtomicFlag f;
    f.set();
    f.set();
    ASSERT_TRUE(f.is_set());
}

TEST(runner, "clear is idempotent") {
    AtomicFlag f;
    f.clear();
    ASSERT_FALSE(f.is_set());
}

TEST(runner, "flag is visible across threads") {
    AtomicFlag f;
    // Gate: ensure single-threaded ops work
    f.set();
    f.clear();

    f.set();

    bool seen = false;
    std::thread t([&f, &seen] {
        seen = f.is_set();
    });
    t.join();

    ASSERT_TRUE(seen);
}

TESTKIT_MAIN(runner)
