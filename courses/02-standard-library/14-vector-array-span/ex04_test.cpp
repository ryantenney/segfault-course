// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("02-14-ex04: Vector of Objects");

TEST(runner, "make_class returns three students") {
    auto students = make_class();
    ASSERT_EQ(students.size(), 3u);
    ASSERT_EQ(students[0].name, std::string("Alice"));
    ASSERT_EQ(students[0].grade, 88);
    ASSERT_EQ(students[1].name, std::string("Bob"));
    ASSERT_EQ(students[1].grade, 95);
    ASSERT_EQ(students[2].name, std::string("Carol"));
    ASSERT_EQ(students[2].grade, 72);
}

TEST(runner, "find_top_student returns the name of the highest-graded student") {
    std::vector<Student> s = {{"Alice", 88}, {"Bob", 95}, {"Carol", 72}};
    ASSERT_EQ(find_top_student(s), std::string("Bob"));
}

TEST(runner, "find_top_student works when top student is first") {
    std::vector<Student> s = {{"Zara", 100}, {"Yuri", 50}};
    ASSERT_EQ(find_top_student(s), std::string("Zara"));
}

TEST(runner, "find_top_student works when top student is last") {
    std::vector<Student> s = {{"Al", 60}, {"Bo", 70}, {"Cy", 99}};
    ASSERT_EQ(find_top_student(s), std::string("Cy"));
}

TEST(runner, "curve_grades adds bonus capped at 100") {
    std::vector<Student> s = {{"Alice", 88}, {"Bob", 95}, {"Carol", 72}};
    curve_grades(s, 10);
    ASSERT_EQ(s[0].grade, 98);   // 88 + 10
    ASSERT_EQ(s[1].grade, 100);  // 95 + 10 = 105, capped at 100
    ASSERT_EQ(s[2].grade, 82);   // 72 + 10
}

TEST(runner, "curve_grades with zero bonus changes nothing") {
    std::vector<Student> s = {{"X", 50}};
    curve_grades(s, 0);
    ASSERT_EQ(s[0].grade, 50);
}

TESTKIT_MAIN(runner)
