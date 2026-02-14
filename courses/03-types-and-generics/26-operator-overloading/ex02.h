// Exercise 02: Defaulted Equality
//
// C++20 lets you ask the compiler to generate operator== for you by writing
// `= default`. The compiler compares each member in declaration order.
// This works for "simple aggregate" types where member-by-member comparison
// is the right definition of equality.
//
// When you default operator==, the compiler also synthesizes operator!= for
// free. This eliminates a common source of bugs: forgetting to update
// operator== when a new member is added.
//
// TODO:
//   1. Replace the body of Rect::operator== with `= default`.
//      Change: bool operator==(const Rect&) const { TODO(); }
//      To:     bool operator==(const Rect&) const = default;
//   2. Replace the body of Employee::operator== with `= default`.
//   3. Implement the gate function `exercise_ready()` by returning true.

#pragma once

#include <string>
#include <testkit/testkit.h>

struct Rect {
    double x;
    double y;
    double width;
    double height;

    // TODO: Replace this with: bool operator==(const Rect&) const = default;
    bool operator==(const Rect& other) const {
        TODO();
    }
};

struct Employee {
    int id;
    std::string name;
    std::string department;

    // TODO: Replace this with: bool operator==(const Employee&) const = default;
    bool operator==(const Employee& other) const {
        TODO();
    }
};

// Gate function: implement this to signal that the exercise is ready.
// Simply return true.
inline bool exercise_ready() {
    TODO();
}
