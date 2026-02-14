// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <thread>

#include "ex03.h"

static testkit::TestRunner runner("04-37-ex03: Bounded Buffer");

TEST(runner, "newly created buffer is empty") {
    BoundedBuffer<int> buf(3);
    // Gate on size()
    auto s = buf.size();
    ASSERT_EQ(s, std::size_t(0));
}

TEST(runner, "put and take a single item") {
    BoundedBuffer<int> buf(3);
    buf.put(42);
    ASSERT_EQ(buf.size(), std::size_t(1));
    int val = buf.take();
    ASSERT_EQ(val, 42);
    ASSERT_EQ(buf.size(), std::size_t(0));
}

TEST(runner, "FIFO ordering is preserved") {
    BoundedBuffer<std::string> buf(5);
    buf.put("first");
    buf.put("second");
    buf.put("third");
    ASSERT_EQ(buf.take(), std::string("first"));
    ASSERT_EQ(buf.take(), std::string("second"));
    ASSERT_EQ(buf.take(), std::string("third"));
}

TEST(runner, "put fills to capacity") {
    BoundedBuffer<int> buf(2);
    buf.put(1);
    buf.put(2);
    ASSERT_EQ(buf.size(), std::size_t(2));
    // Buffer is now full; take one to make room
    ASSERT_EQ(buf.take(), 1);
    buf.put(3);
    ASSERT_EQ(buf.take(), 2);
    ASSERT_EQ(buf.take(), 3);
}

TEST(runner, "take blocks on empty buffer until item is put") {
    BoundedBuffer<int> buf(2);
    // Gate: ensure single-threaded operations work
    buf.put(0);
    buf.take();

    std::thread producer([&buf] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        buf.put(99);
    });

    int val = buf.take();  // should block until producer puts
    ASSERT_EQ(val, 99);
    producer.join();
}

TEST(runner, "put blocks on full buffer until item is taken") {
    BoundedBuffer<int> buf(1);
    buf.put(1);  // buffer is now full

    std::thread consumer([&buf] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        buf.take();  // make room
    });

    buf.put(2);  // should block until consumer takes
    ASSERT_EQ(buf.take(), 2);
    consumer.join();
}

TESTKIT_MAIN(runner)
