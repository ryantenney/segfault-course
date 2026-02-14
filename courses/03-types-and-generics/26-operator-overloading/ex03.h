// Exercise 03: Spaceship Operator
//
// C++20 introduced the three-way comparison operator (<=>), nicknamed the
// "spaceship operator". When you default it, the compiler generates all six
// comparison operators (==, !=, <, <=, >, >=) for free.
//
// The return type of <=> is one of:
//   - std::strong_ordering   (like int comparison: exactly one of <, ==, >)
//   - std::weak_ordering     (equivalence, not true equality)
//   - std::partial_ordering  (some values are incomparable, like NaN)
//
// For simple aggregates with int/string members, defaulting <=> gives you
// std::strong_ordering and lexicographic comparison in declaration order.
//
// TODO:
//   1. Replace the body of Version::operator<=> with `= default`.
//      Change: auto operator<=>(const Version&) const { TODO(); ... }
//      To:     auto operator<=>(const Version&) const = default;
//   2. Replace the body of FullName::operator<=> with `= default`.
//      This compares last_name first (because it's declared first), then
//      first_name — which is the natural alphabetical ordering for names.
//   3. Implement the gate function `exercise_ready()` by returning true.

#pragma once

#include <compare>
#include <string>
#include <testkit/testkit.h>

struct Version {
    int major;
    int minor;
    int patch;

    // TODO: Replace this with: auto operator<=>(const Version&) const = default;
    std::strong_ordering operator<=>(const Version& other) const {
        TODO();
        return std::strong_ordering::equal;
    }

    // Needed alongside <=> for == and != to work with defaulted <=>
    bool operator==(const Version&) const = default;
};

struct FullName {
    std::string last_name;
    std::string first_name;

    // TODO: Replace this with: auto operator<=>(const FullName&) const = default;
    std::strong_ordering operator<=>(const FullName& other) const {
        TODO();
        return std::strong_ordering::equal;
    }

    // Needed alongside <=> for == and != to work with defaulted <=>
    bool operator==(const FullName&) const = default;
};

// Gate function: implement this to signal that the exercise is ready.
// Simply return true.
inline bool exercise_ready() {
    TODO();
}
