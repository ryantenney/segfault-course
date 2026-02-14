// Exercise 04 — Tests (read-only)
//
// Verifies safe reference downcasting with dynamic_cast and std::bad_cast.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("01-08-ex04: Safe Downcasting (Reference)");

TEST(runner, "try_dog_speak returns Woof for Dog") {
    Dog d;
    ASSERT_EQ(try_dog_speak(d), std::string("Woof"));
}

TEST(runner, "try_dog_speak returns unknown for Cat") {
    Cat c;
    ASSERT_EQ(try_dog_speak(c), std::string("unknown"));
}

TEST(runner, "try_dog_speak returns unknown for Fish") {
    Fish f;
    ASSERT_EQ(try_dog_speak(f), std::string("unknown"));
}

TEST(runner, "try_cat_speak returns Meow for Cat") {
    Cat c;
    ASSERT_EQ(try_cat_speak(c), std::string("Meow"));
}

TEST(runner, "try_cat_speak returns unknown for Dog") {
    Dog d;
    ASSERT_EQ(try_cat_speak(d), std::string("unknown"));
}

TESTKIT_MAIN(runner)
