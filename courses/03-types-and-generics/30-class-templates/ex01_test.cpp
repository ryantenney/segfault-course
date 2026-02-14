// Exercise 01 -- Tests (read-only)
//
// Verifies that Stack<T> works correctly with different types.

#include <testkit/testkit.h>
#include <string>
#include "ex01.h"

static testkit::TestRunner runner("03-30-ex01: Generic Stack");

TEST(runner, "newly created stack is empty") {
    Stack<int> s;
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.size(), std::size_t(0));
}

TEST(runner, "push increases size") {
    Stack<int> s;
    s.push(42);
    ASSERT_FALSE(s.empty());
    ASSERT_EQ(s.size(), std::size_t(1));
}

TEST(runner, "top returns last pushed element") {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    ASSERT_EQ(s.top(), 30);
}

TEST(runner, "pop removes the top element") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.top(), 1);
    ASSERT_EQ(s.size(), std::size_t(1));
}

TEST(runner, "pop on empty stack throws out_of_range") {
    Stack<int> s;
    ASSERT_THROWS(s.pop(), std::out_of_range);
}

TEST(runner, "top on empty stack throws out_of_range") {
    Stack<int> s;
    ASSERT_THROWS(s.top(), std::out_of_range);
}

TEST(runner, "works with std::string") {
    Stack<std::string> s;
    s.push("hello");
    s.push("world");
    ASSERT_EQ(s.top(), std::string("world"));
    s.pop();
    ASSERT_EQ(s.top(), std::string("hello"));
}

TEST(runner, "push-pop sequence restores empty") {
    Stack<double> s;
    s.push(3.14);
    s.push(2.72);
    s.pop();
    s.pop();
    ASSERT_TRUE(s.empty());
}

TESTKIT_MAIN(runner)
