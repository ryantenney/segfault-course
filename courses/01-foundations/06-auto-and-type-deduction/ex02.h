// Exercise 02: auto with const/reference
//
// PROBLEM:
//   auto by itself strips top-level const and references. This can lead
//   to surprising copies or lost immutability. You need to combine auto
//   with const and & to get the behavior you want.
//
//   - auto        → deduces value (copies)
//   - auto&       → deduces lvalue reference
//   - const auto& → deduces const lvalue reference (no copy, no mutation)
//
// TODO:
//   Implement each function using the correct form of auto.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// Return the first element of the vector by value (a copy).
// Use auto (not auto&) to capture the element.
inline int first_copy(const std::vector<int>& v) {
    TODO();
    // Hint: auto val = v.front(); return val;
}

// Return a const reference to the last element.
// Use const auto& to avoid copying.
inline const std::string& last_ref(const std::vector<std::string>& v) {
    TODO();
    // Hint: const auto& ref = v.back(); return ref;
}

// Double every element in the vector in-place.
// Use auto& in a range-for to modify elements.
inline void double_all(std::vector<int>& v) {
    TODO();
    // Hint: for (auto& elem : v) { elem *= 2; }
}

// Count how many strings have length > threshold.
// Use const auto& to avoid copying strings.
inline int count_long_strings(const std::vector<std::string>& v, int threshold) {
    TODO();
    // Hint: for (const auto& s : v) { if (s.size() > threshold) ++count; }
}
