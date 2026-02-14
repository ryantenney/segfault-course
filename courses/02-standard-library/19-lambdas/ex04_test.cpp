// Exercise 04 -- Tests (read-only)

#include <memory>
#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("02-19-ex04: Capture by Move");

TEST(runner, "capture_unique_ptr returns correct value") {
    auto fn = capture_unique_ptr(42);
    ASSERT_EQ(fn(), 42);
}

TEST(runner, "capture_unique_ptr lambda is callable multiple times") {
    auto fn = capture_unique_ptr(99);
    ASSERT_EQ(fn(), 99);
    ASSERT_EQ(fn(), 99);
}

TEST(runner, "capture_unique_ptr with zero") {
    auto fn = capture_unique_ptr(0);
    ASSERT_EQ(fn(), 0);
}

TEST(runner, "capture_string_by_move returns correct length") {
    auto fn = capture_string_by_move("hello");
    ASSERT_EQ(fn(), 5u);
}

TEST(runner, "capture_string_by_move with empty string") {
    auto fn = capture_string_by_move("");
    ASSERT_EQ(fn(), 0u);
}

TEST(runner, "capture_string_by_move lambda is callable multiple times") {
    auto fn = capture_string_by_move("test");
    ASSERT_EQ(fn(), 4u);
    ASSERT_EQ(fn(), 4u);
}

TEST(runner, "transfer_ownership returns correct value") {
    auto ptr = std::make_unique<int>(77);
    auto fn = transfer_ownership(std::move(ptr));
    ASSERT_EQ(fn(), 77);
}

TEST(runner, "transfer_ownership takes ownership from caller") {
    auto ptr = std::make_unique<int>(55);
    auto fn = transfer_ownership(std::move(ptr));
    // ptr should be null after move
    ASSERT_TRUE(ptr == nullptr);
    ASSERT_EQ(fn(), 55);
}

TEST(runner, "transfer_ownership lambda is callable multiple times") {
    auto ptr = std::make_unique<int>(33);
    auto fn = transfer_ownership(std::move(ptr));
    ASSERT_EQ(fn(), 33);
    ASSERT_EQ(fn(), 33);
}

TESTKIT_MAIN(runner)
