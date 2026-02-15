// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex07.h"

static testkit::TestRunner runner("05-48-ex07: Event Filtering");

TEST(runner, "callback is called when predicate returns true") {
    FilterEmitter<int> emitter;
    int received = 0;
    emitter.on(
        [](const int& v) { return v > 0; },
        [&received](const int& v) { received = v; });
    emitter.emit(42);
    ASSERT_EQ(received, 42);
}

TEST(runner, "callback is NOT called when predicate returns false") {
    FilterEmitter<int> emitter;
    int received = -1;
    emitter.on(
        [](const int& v) { return v > 100; },
        [&received](const int& v) { received = v; });
    emitter.emit(50);
    ASSERT_EQ(received, -1);
}

TEST(runner, "multiple listeners with different filters") {
    FilterEmitter<int> emitter;
    std::vector<int> evens;
    std::vector<int> odds;
    emitter.on(
        [](const int& v) { return v % 2 == 0; },
        [&evens](const int& v) { evens.push_back(v); });
    emitter.on(
        [](const int& v) { return v % 2 != 0; },
        [&odds](const int& v) { odds.push_back(v); });

    emitter.emit(1);
    emitter.emit(2);
    emitter.emit(3);
    emitter.emit(4);

    ASSERT_EQ(evens.size(), std::size_t(2));
    ASSERT_EQ(evens[0], 2);
    ASSERT_EQ(evens[1], 4);
    ASSERT_EQ(odds.size(), std::size_t(2));
    ASSERT_EQ(odds[0], 1);
    ASSERT_EQ(odds[1], 3);
}

TEST(runner, "listener_count reflects all registered listeners") {
    FilterEmitter<std::string> emitter;
    emitter.on(
        [](const std::string&) { return true; },
        [](const std::string&) {});
    emitter.on(
        [](const std::string&) { return false; },
        [](const std::string&) {});
    ASSERT_EQ(emitter.listener_count(), std::size_t(2));
}

TEST(runner, "emit with no matching listeners calls no callbacks") {
    FilterEmitter<int> emitter;
    int count = 0;
    emitter.on(
        [](const int& v) { return v > 1000; },
        [&count](const int&) { ++count; });
    emitter.emit(1);
    emitter.emit(2);
    emitter.emit(3);
    ASSERT_EQ(count, 0);
}

TESTKIT_MAIN(runner)
