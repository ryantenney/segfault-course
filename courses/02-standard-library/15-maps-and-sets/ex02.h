// Exercise 02: Safe Lookup
//
// Using operator[] for lookup on an unordered_map silently inserts a
// default-constructed value if the key isn't found. This is dangerous
// for non-mutating lookups because it modifies the map.
//
// Safer alternatives:
//   - find(key): returns an iterator (end() if not found)
//   - contains(key): returns bool (C++20)
//   - at(key): returns a reference, throws std::out_of_range if not found
//
// TODO:
//   Implement the three functions below using find() and contains()
//   instead of operator[].

#pragma once

#include <testkit/testkit.h>
#include <unordered_map>
#include <string>

// Look up a student's grade by name.
// Return the grade if found, or -1 if the student is not in the map.
// Use find() — do NOT use operator[].
inline int lookup_grade(const std::unordered_map<std::string, int>& grades,
                        const std::string& name) {
    TODO();
}

// Return true if the student exists in the map, false otherwise.
// Use contains() (C++20).
inline bool has_student(const std::unordered_map<std::string, int>& grades,
                        const std::string& name) {
    TODO();
}

// Count how many students have a grade >= passing_grade.
// Iterate over the map using a range-for loop.
inline int count_passing(const std::unordered_map<std::string, int>& grades,
                         int passing_grade) {
    TODO();
}
