// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <memory>

#include "ex06.h"

// Concrete observer for testing.
class CountingObserver : public Observer {
public:
    int count = 0;
    void on_event() override { ++count; }
};

static testkit::TestRunner runner("05-48-ex06: Weak Observer");

TEST(runner, "subscribe adds an observer") {
    WeakEmitter emitter;
    auto obs = std::make_shared<CountingObserver>();
    emitter.subscribe(obs);
    ASSERT_EQ(emitter.subscriber_count(), std::size_t(1));
}

TEST(runner, "emit notifies live observers") {
    WeakEmitter emitter;
    auto obs = std::make_shared<CountingObserver>();
    emitter.subscribe(obs);
    emitter.emit();
    ASSERT_EQ(obs->count, 1);
    emitter.emit();
    ASSERT_EQ(obs->count, 2);
}

TEST(runner, "emit skips expired observers without crashing") {
    WeakEmitter emitter;
    auto obs1 = std::make_shared<CountingObserver>();
    auto obs2 = std::make_shared<CountingObserver>();
    emitter.subscribe(obs1);
    emitter.subscribe(obs2);

    // Destroy obs1
    obs1.reset();

    // emit should skip the expired one and still notify obs2
    emitter.emit();
    ASSERT_EQ(obs2->count, 1);
}

TEST(runner, "cleanup removes expired entries") {
    WeakEmitter emitter;
    auto obs = std::make_shared<CountingObserver>();
    emitter.subscribe(obs);
    ASSERT_EQ(emitter.subscriber_count(), std::size_t(1));

    obs.reset();  // observer destroyed
    emitter.cleanup();
    ASSERT_EQ(emitter.subscriber_count(), std::size_t(0));
}

TEST(runner, "cleanup keeps live entries") {
    WeakEmitter emitter;
    auto live = std::make_shared<CountingObserver>();
    auto dead = std::make_shared<CountingObserver>();
    emitter.subscribe(live);
    emitter.subscribe(dead);
    dead.reset();
    emitter.cleanup();
    ASSERT_EQ(emitter.subscriber_count(), std::size_t(1));
    emitter.emit();
    ASSERT_EQ(live->count, 1);
}

TESTKIT_MAIN(runner)
