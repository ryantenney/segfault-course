// Exercise 06 -- Tests (read-only)
//
// Verifies the copy-and-swap idiom implementation for SwapBuffer.

#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("03-28-ex06: Copy-and-Swap Idiom");

TEST(runner, "swap exchanges contents") {
    SwapBuffer a(2);
    a[0] = 1;
    a[1] = 2;

    SwapBuffer b(3);
    b[0] = 10;
    b[1] = 20;
    b[2] = 30;

    a.swap(b);

    ASSERT_EQ(a.size(), 3u);
    ASSERT_EQ(a[0], 10);
    ASSERT_EQ(a[1], 20);
    ASSERT_EQ(a[2], 30);

    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
}

TEST(runner, "copy constructor creates deep copy") {
    SwapBuffer a(3);
    a[0] = 5;
    a[1] = 6;
    a[2] = 7;

    SwapBuffer b(a);

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 5);
    ASSERT_EQ(b[1], 6);
    ASSERT_EQ(b[2], 7);
    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "move constructor steals resources") {
    SwapBuffer a(2);
    a[0] = 42;
    a[1] = 43;
    const int* original_data = a.data();

    SwapBuffer b(std::move(a));

    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b[0], 42);
    ASSERT_EQ(b[1], 43);
    ASSERT_TRUE(b.data() == original_data);
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_EQ(a.size(), 0u);
}

TEST(runner, "copy assignment via copy-and-swap") {
    SwapBuffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    SwapBuffer b(1);
    b = a;

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[2], 3);
    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "self-assignment is safe via copy-and-swap") {
    SwapBuffer a(3);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    a = a;

    ASSERT_EQ(a.size(), 3u);
    ASSERT_EQ(a[0], 10);
    ASSERT_EQ(a[1], 20);
    ASSERT_EQ(a[2], 30);
}

TEST(runner, "move assignment works via copy-and-swap") {
    SwapBuffer a(2);
    a[0] = 7;
    a[1] = 8;

    SwapBuffer b(1);
    b = std::move(a);

    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b[0], 7);
    ASSERT_EQ(b[1], 8);
}

TEST(runner, "free function swap works") {
    SwapBuffer a(1);
    a[0] = 100;

    SwapBuffer b(1);
    b[0] = 200;

    swap(a, b);

    ASSERT_EQ(a[0], 200);
    ASSERT_EQ(b[0], 100);
}

TESTKIT_MAIN(runner)
