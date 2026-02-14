// Exercise 01 -- Tests (read-only)
//
// Verifies CRTP instance counting with Counter<Derived>.

#include <testkit/testkit.h>
#include <vector>
#include "ex01.h"

static testkit::TestRunner runner("03-34-ex01: CRTP Counter");

TEST(runner, "Dog::name returns the stored name") {
    Dog d("Rex");
    ASSERT_EQ(d.name(), std::string("Rex"));
}

TEST(runner, "Cat::name returns the stored name") {
    Cat c("Whiskers");
    ASSERT_EQ(c.name(), std::string("Whiskers"));
}

TEST(runner, "Counter<Dog> tracks Dog instances independently") {
    // Gate: ensure name() is implemented so Dog is usable.
    Dog gate("gate");
    gate.name();

    int before = Dog::count();
    {
        Dog a("A");
        Dog b("B");
        ASSERT_EQ(Dog::count(), before + 2);
    }
    ASSERT_EQ(Dog::count(), before);
}

TEST(runner, "Counter<Cat> tracks Cat instances independently") {
    Cat gate("gate");
    gate.name();

    int before = Cat::count();
    {
        Cat a("A");
        ASSERT_EQ(Cat::count(), before + 1);
    }
    ASSERT_EQ(Cat::count(), before);
}

TEST(runner, "Dog and Cat counts are independent") {
    Dog dg("gate");
    dg.name();

    int dog_before = Dog::count();
    int cat_before = Cat::count();
    {
        Dog d("Fido");
        ASSERT_EQ(Dog::count(), dog_before + 1);
        ASSERT_EQ(Cat::count(), cat_before);  // unchanged
    }
    ASSERT_EQ(Dog::count(), dog_before);
}

TEST(runner, "make_dogs creates a vector with correct names") {
    std::vector<std::string> names = {"Alpha", "Beta", "Gamma"};
    auto dogs = make_dogs(names);

    ASSERT_EQ(dogs.size(), 3u);
    ASSERT_EQ(dogs[0].name(), std::string("Alpha"));
    ASSERT_EQ(dogs[1].name(), std::string("Beta"));
    ASSERT_EQ(dogs[2].name(), std::string("Gamma"));
}

TEST(runner, "total_animals returns sum of Dog and Cat counts") {
    int base = total_animals();
    {
        Dog d1("D1");
        Dog d2("D2");
        Cat c1("C1");
        ASSERT_EQ(total_animals(), base + 3);
    }
    ASSERT_EQ(total_animals(), base);
}

TESTKIT_MAIN(runner)
