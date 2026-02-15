// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex04.h"

static testkit::TestRunner runner("05-48-ex04: Event with Payload");

TEST(runner, "listener receives the emitted value") {
    TypedEmitter<int> emitter;
    int received = 0;
    emitter.on([&received](const int& val) { received = val; });
    emitter.emit(42);
    ASSERT_EQ(received, 42);
}

TEST(runner, "multiple listeners all receive the payload") {
    TypedEmitter<std::string> emitter;
    std::vector<std::string> results;
    emitter.on([&results](const std::string& s) { results.push_back(s); });
    emitter.on([&results](const std::string& s) { results.push_back(s + "!"); });
    emitter.emit("hello");
    ASSERT_EQ(results.size(), std::size_t(2));
    ASSERT_EQ(results[0], std::string("hello"));
    ASSERT_EQ(results[1], std::string("hello!"));
}

TEST(runner, "each emit delivers the current value") {
    TypedEmitter<int> emitter;
    std::vector<int> log;
    emitter.on([&log](const int& val) { log.push_back(val); });
    emitter.emit(1);
    emitter.emit(2);
    emitter.emit(3);
    ASSERT_EQ(log.size(), std::size_t(3));
    ASSERT_EQ(log[0], 1);
    ASSERT_EQ(log[1], 2);
    ASSERT_EQ(log[2], 3);
}

TEST(runner, "listener_count tracks registrations") {
    TypedEmitter<double> emitter;
    ASSERT_EQ(emitter.listener_count(), std::size_t(0));
    emitter.on([](const double&) {});
    emitter.on([](const double&) {});
    ASSERT_EQ(emitter.listener_count(), std::size_t(2));
}

TEST(runner, "works with struct payloads") {
    struct Event {
        int code;
        std::string message;
    };

    TypedEmitter<Event> emitter;
    int received_code = 0;
    std::string received_msg;
    emitter.on([&](const Event& e) {
        received_code = e.code;
        received_msg = e.message;
    });
    emitter.emit(Event{200, "OK"});
    ASSERT_EQ(received_code, 200);
    ASSERT_EQ(received_msg, std::string("OK"));
}

TESTKIT_MAIN(runner)
