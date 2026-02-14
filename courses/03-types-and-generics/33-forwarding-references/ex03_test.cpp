// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("03-33-ex03: Perfect Forwarding Wrapper");

// A Tracker that records whether it was copied or moved.
struct Tracker {
    std::string label;
    bool was_copied = false;
    bool was_moved = false;

    explicit Tracker(std::string l) : label(std::move(l)) {}

    Tracker(const Tracker& other)
        : label(other.label), was_copied(true), was_moved(false) {}

    Tracker(Tracker&& other) noexcept
        : label(std::move(other.label)), was_copied(false), was_moved(true) {
        other.label = "(moved)";
    }

    Tracker& operator=(const Tracker&) = default;
    Tracker& operator=(Tracker&&) = default;
};

TEST(runner, "log_and_call increments call_count") {
    call_count = 0;
    log_and_call([]() {});
    ASSERT_EQ(call_count, 1);
}

TEST(runner, "log_and_call forwards return value") {
    auto result = log_and_call([](int a, int b) { return a + b; }, 3, 4);
    ASSERT_EQ(result, 7);
}

TEST(runner, "log_and_call forwards lvalue without copying") {
    Tracker t("hello");
    auto check = [](Tracker& tr) -> std::string { return tr.label; };
    auto result = log_and_call(check, t);
    ASSERT_EQ(result, std::string("hello"));
    // t should not have been moved from
    ASSERT_EQ(t.label, std::string("hello"));
}

TEST(runner, "log_and_call forwards rvalue (enables move)") {
    auto check = [](Tracker tr) -> std::string { return tr.label; };
    auto result = log_and_call(check, Tracker("world"));
    ASSERT_EQ(result, std::string("world"));
}

TEST(runner, "log_and_call preserves lvalue string ref") {
    std::string s = "original";
    auto modify = [](std::string& str) { str += "_modified"; };
    log_and_call(modify, s);
    ASSERT_EQ(s, std::string("original_modified"));
}

TEST(runner, "call_count increments across multiple calls") {
    call_count = 0;
    log_and_call([]() {});
    log_and_call([]() {});
    log_and_call([]() {});
    ASSERT_EQ(call_count, 3);
}

TESTKIT_MAIN(runner)
