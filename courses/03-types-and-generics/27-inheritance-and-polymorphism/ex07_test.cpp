// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex07.h"

static testkit::TestRunner runner("03-27-ex07: Object Slicing");

TEST(runner, "Instrument plays default sound") {
    Instrument inst;
    ASSERT_EQ(inst.play(), std::string("..."));
}

TEST(runner, "Guitar plays Twang") {
    Guitar g;
    ASSERT_EQ(g.play(), std::string("Twang!"));
}

TEST(runner, "Drum plays Boom") {
    Drum d;
    ASSERT_EQ(d.play(), std::string("Boom!"));
}

TEST(runner, "play_by_value slices Guitar to Instrument") {
    Guitar g;
    // Passing by value slices the Guitar — only the Instrument part is copied.
    std::string result = play_by_value(g);
    ASSERT_EQ(result, std::string("..."));
}

TEST(runner, "play_by_value slices Drum to Instrument") {
    Drum d;
    std::string result = play_by_value(d);
    ASSERT_EQ(result, std::string("..."));
}

TEST(runner, "play_by_reference preserves Guitar polymorphism") {
    Guitar g;
    std::string result = play_by_reference(g);
    ASSERT_EQ(result, std::string("Twang!"));
}

TEST(runner, "play_by_reference preserves Drum polymorphism") {
    Drum d;
    std::string result = play_by_reference(d);
    ASSERT_EQ(result, std::string("Boom!"));
}

TEST(runner, "play_by_reference with base Instrument") {
    Instrument inst;
    std::string result = play_by_reference(inst);
    ASSERT_EQ(result, std::string("..."));
}

TESTKIT_MAIN(runner)
