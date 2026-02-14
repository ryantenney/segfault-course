// Exercise 02 -- Tests (read-only)
//
// Verifies that Queue<T> works with out-of-line member definitions.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("03-30-ex02: Out-of-Line Members");

TEST(runner, "newly created queue is empty") {
    Queue<int> q;
    ASSERT_TRUE(q.empty());
    ASSERT_EQ(q.size(), std::size_t(0));
}

TEST(runner, "enqueue adds to the back") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    ASSERT_EQ(q.front(), 10);
    ASSERT_EQ(q.size(), std::size_t(2));
}

TEST(runner, "dequeue removes from the front") {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    ASSERT_EQ(q.dequeue(), 1);
    ASSERT_EQ(q.dequeue(), 2);
    ASSERT_EQ(q.dequeue(), 3);
}

TEST(runner, "dequeue on empty queue throws out_of_range") {
    Queue<int> q;
    ASSERT_THROWS(q.dequeue(), std::out_of_range);
}

TEST(runner, "front on empty queue throws out_of_range") {
    Queue<int> q;
    ASSERT_THROWS(q.front(), std::out_of_range);
}

TEST(runner, "works with std::string") {
    Queue<std::string> q;
    q.enqueue("alpha");
    q.enqueue("beta");
    ASSERT_EQ(q.front(), std::string("alpha"));
    ASSERT_EQ(q.dequeue(), std::string("alpha"));
    ASSERT_EQ(q.front(), std::string("beta"));
}

TEST(runner, "enqueue-dequeue cycle") {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();
    q.enqueue(3);
    ASSERT_EQ(q.size(), std::size_t(2));
    ASSERT_EQ(q.dequeue(), 2);
    ASSERT_EQ(q.dequeue(), 3);
    ASSERT_TRUE(q.empty());
}

TESTKIT_MAIN(runner)
