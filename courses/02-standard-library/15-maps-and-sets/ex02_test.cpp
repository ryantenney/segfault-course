// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("02-15-ex02: Safe Lookup");

TEST(runner, "lookup_grade returns grade when student exists") {
    std::unordered_map<std::string, int> grades = {
        {"Alice", 92}, {"Bob", 78}, {"Carol", 85}
    };
    ASSERT_EQ(lookup_grade(grades, "Alice"), 92);
    ASSERT_EQ(lookup_grade(grades, "Bob"), 78);
}

TEST(runner, "lookup_grade returns -1 when student not found") {
    std::unordered_map<std::string, int> grades = {
        {"Alice", 92}, {"Bob", 78}
    };
    ASSERT_EQ(lookup_grade(grades, "Dave"), -1);
    ASSERT_EQ(lookup_grade(grades, ""), -1);
}

TEST(runner, "lookup_grade does not modify the map") {
    std::unordered_map<std::string, int> grades = {{"Alice", 92}};
    lookup_grade(grades, "NotFound");
    ASSERT_EQ(grades.size(), 1u);  // map should not have grown
}

TEST(runner, "has_student returns true for existing students") {
    std::unordered_map<std::string, int> grades = {
        {"Alice", 92}, {"Bob", 78}
    };
    ASSERT_TRUE(has_student(grades, "Alice"));
    ASSERT_TRUE(has_student(grades, "Bob"));
}

TEST(runner, "has_student returns false for missing students") {
    std::unordered_map<std::string, int> grades = {
        {"Alice", 92}, {"Bob", 78}
    };
    ASSERT_FALSE(has_student(grades, "Charlie"));
    ASSERT_FALSE(has_student(grades, ""));
}

TEST(runner, "count_passing counts students at or above threshold") {
    std::unordered_map<std::string, int> grades = {
        {"Alice", 92}, {"Bob", 58}, {"Carol", 85}, {"Dave", 60}
    };
    ASSERT_EQ(count_passing(grades, 60), 3);  // Alice, Carol, Dave
    ASSERT_EQ(count_passing(grades, 90), 1);  // Alice only
    ASSERT_EQ(count_passing(grades, 100), 0);
}

TEST(runner, "count_passing on empty map returns zero") {
    std::unordered_map<std::string, int> empty;
    ASSERT_EQ(count_passing(empty, 0), 0);
}

TESTKIT_MAIN(runner)
