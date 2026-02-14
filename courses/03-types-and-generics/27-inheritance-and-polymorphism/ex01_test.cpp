// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex01.h"

static testkit::TestRunner runner("03-27-ex01: Basic Inheritance");

TEST(runner, "Student can be created with name, age, and major") {
    Student s = create_student("Alice", 20, "Computer Science");
    ASSERT_EQ(s.major(), std::string("Computer Science"));
}

TEST(runner, "Student inherits name() from Person") {
    Student s = create_student("Bob", 21, "Physics");
    ASSERT_EQ(s.name(), std::string("Bob"));
}

TEST(runner, "Student inherits age() from Person") {
    Student s = create_student("Carol", 22, "Math");
    ASSERT_EQ(s.age(), 22);
}

TEST(runner, "describe returns formatted string") {
    Student s = create_student("Alice", 20, "Computer Science");
    ASSERT_EQ(s.describe(), std::string("Alice, age 20, Computer Science"));
}

TEST(runner, "describe works with different data") {
    Student s = create_student("Dave", 25, "Art");
    ASSERT_EQ(s.describe(), std::string("Dave, age 25, Art"));
}

TESTKIT_MAIN(runner)
