// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>

#include "ex07.h"

static testkit::TestRunner runner("04-38-ex07: Memory Order Awareness");

TEST(runner, "consume returns -1 before publish") {
    SequencedStore ss;
    int val = ss.consume();
    ASSERT_EQ(val, -1);
}

TEST(runner, "publish makes payload available via consume") {
    SequencedStore ss;
    ss.publish(42);
    int val = ss.consume();
    ASSERT_EQ(val, 42);
}

TEST(runner, "publish overwrites previous payload") {
    SequencedStore ss;
    ss.publish(10);
    ss.publish(20);
    ASSERT_EQ(ss.consume(), 20);
}

TEST(runner, "payload_relaxed returns the stored value") {
    SequencedStore ss;
    ss.publish(99);
    // After publish on same thread, relaxed load is fine
    ASSERT_EQ(ss.payload_relaxed(), 99);
}

TEST(runner, "payload_relaxed returns 0 before any publish") {
    SequencedStore ss;
    // Gate: call consume to verify it works
    ss.consume();
    ASSERT_EQ(ss.payload_relaxed(), 0);
}

TEST(runner, "publish on one thread is visible to consume on another") {
    SequencedStore ss;
    // Gate: ensure single-threaded ops work
    ss.publish(0);
    ss.consume();

    ss.publish(77);

    int seen = -1;
    std::thread t([&ss, &seen] {
        seen = ss.consume();
    });
    t.join();

    ASSERT_EQ(seen, 77);
}

TEST(runner, "acquire-release ensures payload is visible after ready") {
    SequencedStore ss;
    // Gate
    ss.publish(0);
    ss.consume();

    // Reset for the real test
    SequencedStore ss2;

    std::thread writer([&ss2] {
        ss2.publish(123);
    });
    writer.join();

    // After the writer thread joins, the publish is guaranteed visible
    int val = ss2.consume();
    ASSERT_EQ(val, 123);
}

TESTKIT_MAIN(runner)
