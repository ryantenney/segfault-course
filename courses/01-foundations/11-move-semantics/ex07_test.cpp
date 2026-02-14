// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-11-ex07: Return Value Optimization");

TEST(runner, "prvalue return: guaranteed RVO, no copies or moves") {
    Tracker::reset();
    auto t = make_tracker("rvo");
    ASSERT_EQ(t.label, std::string("rvo"));
    ASSERT_EQ(Tracker::copies, 0);
    ASSERT_EQ(Tracker::moves, 0);
}

TEST(runner, "named return: NRVO typically elides copy and move") {
    Tracker::reset();
    auto t = make_named_tracker("nrvo");
    ASSERT_EQ(t.label, std::string("nrvo"));
    ASSERT_EQ(Tracker::copies, 0);
    // NRVO is not guaranteed, but all major compilers apply it.
    // If this fails on your compiler, that's technically allowed.
    ASSERT_EQ(Tracker::moves, 0);
}

TEST(runner, "parameter return: no RVO, but implicit move occurs") {
    Tracker::reset();
    Tracker input("param");
    Tracker::reset(); // reset after constructing input
    auto t = passthrough_tracker(std::move(input));
    ASSERT_EQ(t.label, std::string("param"));
    // One move into the parameter + one move on return (parameter is implicitly moved)
    ASSERT_EQ(Tracker::copies, 0);
    ASSERT_TRUE(Tracker::moves >= 1);
}

TEST(runner, "std::move on local return inhibits NRVO") {
    Tracker::reset();
    auto t = move_tracker_bad("bad");
    ASSERT_EQ(t.label, std::string("bad"));
    ASSERT_EQ(Tracker::copies, 0);
    // std::move prevents NRVO, forcing at least one move
    ASSERT_TRUE(Tracker::moves >= 1);
}

TESTKIT_MAIN(runner)
