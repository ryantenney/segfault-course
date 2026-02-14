// Exercise 04: Vector of Objects
//
// Vectors can hold any copyable or movable type, including your own structs.
// This exercise practices storing custom objects in a vector, iterating
// over them, and modifying their fields.
//
// TODO:
//   Implement the three functions below that work with a vector of Students.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int grade;
};

// Create and return a vector containing three students:
//   {"Alice", 88}, {"Bob", 95}, {"Carol", 72}
inline std::vector<Student> make_class() {
    TODO();
}

// Return the name of the student with the highest grade.
// You may assume the vector is non-empty.
inline std::string find_top_student(const std::vector<Student>& students) {
    TODO();
}

// Add `bonus` points to every student's grade, but cap each grade at 100.
// Modify the vector in place.
inline void curve_grades(std::vector<Student>& students, int bonus) {
    TODO();
}
