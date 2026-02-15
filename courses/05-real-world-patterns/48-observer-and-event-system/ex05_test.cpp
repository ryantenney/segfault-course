// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("05-48-ex05: Auto-unsubscribe");

TEST(runner, "subscription auto-removes listener on destruction") {
    SubEmitter e;
    int count = 0;
    {
        uint64_t id = e.on([&count] { ++count; });
        Subscription sub(&e, id);
        ASSERT_EQ(e.listener_count(), std::size_t(1));
    }
    // sub destroyed — listener should be removed
    ASSERT_EQ(e.listener_count(), std::size_t(0));
    e.emit();
    ASSERT_EQ(count, 0);
}

TEST(runner, "moved subscription does not double-unsubscribe") {
    SubEmitter e;
    int count = 0;
    uint64_t id = e.on([&count] { ++count; });
    {
        Subscription s1(&e, id);
        {
            Subscription s2(std::move(s1));
            // s2 owns the subscription now
        }
        // s2 destroyed — listener removed
        ASSERT_EQ(e.listener_count(), std::size_t(0));
        // s1 destroyed here — should NOT double-remove
    }
    ASSERT_EQ(e.listener_count(), std::size_t(0));
}

TEST(runner, "release disarms the subscription") {
    SubEmitter e;
    int count = 0;
    uint64_t id = e.on([&count] { ++count; });
    {
        Subscription sub(&e, id);
        uint64_t released_id = sub.release();
        ASSERT_EQ(released_id, id);
    }
    // sub destroyed, but release() was called — listener stays
    ASSERT_EQ(e.listener_count(), std::size_t(1));
    e.emit();
    ASSERT_EQ(count, 1);
    // Manual cleanup
    e.off(id);
}

TEST(runner, "move assignment unsubscribes the old target") {
    SubEmitter e;
    int a_count = 0, b_count = 0;
    uint64_t id_a = e.on([&a_count] { ++a_count; });
    uint64_t id_b = e.on([&b_count] { ++b_count; });
    ASSERT_EQ(e.listener_count(), std::size_t(2));

    Subscription sub_a(&e, id_a);
    Subscription sub_b(&e, id_b);
    // Move sub_b into sub_a. sub_a's old subscription (id_a) should be removed.
    sub_a = std::move(sub_b);
    ASSERT_EQ(e.listener_count(), std::size_t(1));
    e.emit();
    ASSERT_EQ(a_count, 0);  // a was removed
    ASSERT_EQ(b_count, 1);  // b still active
}

TESTKIT_MAIN(runner)
