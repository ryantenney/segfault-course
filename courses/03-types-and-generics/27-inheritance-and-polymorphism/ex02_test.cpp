// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>
#include <memory>
#include <string>

#include "ex02.h"

static testkit::TestRunner runner("03-27-ex02: Virtual Method Dispatch");

TEST(runner, "Dog speaks Woof") {
    Dog d;
    ASSERT_EQ(d.speak(), std::string("Woof"));
}

TEST(runner, "Cat speaks Meow") {
    Cat c;
    ASSERT_EQ(c.speak(), std::string("Meow"));
}

TEST(runner, "Dog type is Dog") {
    Dog d;
    ASSERT_EQ(d.type(), std::string("Dog"));
}

TEST(runner, "Cat type is Cat") {
    Cat c;
    ASSERT_EQ(c.type(), std::string("Cat"));
}

TEST(runner, "virtual dispatch through base pointer works for Dog") {
    std::unique_ptr<Animal> a = make_dog();
    ASSERT_EQ(a->speak(), std::string("Woof"));
    ASSERT_EQ(a->type(), std::string("Dog"));
}

TEST(runner, "virtual dispatch through base pointer works for Cat") {
    std::unique_ptr<Animal> a = make_cat();
    ASSERT_EQ(a->speak(), std::string("Meow"));
    ASSERT_EQ(a->type(), std::string("Cat"));
}

TEST(runner, "virtual dispatch through base reference") {
    Dog d;
    Cat c;
    const Animal& a1 = d;
    const Animal& a2 = c;
    ASSERT_EQ(a1.speak(), std::string("Woof"));
    ASSERT_EQ(a2.speak(), std::string("Meow"));
}

TESTKIT_MAIN(runner)
