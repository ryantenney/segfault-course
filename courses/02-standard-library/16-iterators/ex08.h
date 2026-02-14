// Exercise 08: Custom Iterator
//
// For a class to work with range-based for loops, it needs to provide
// begin() and end() methods that return iterators. An iterator must
// support three operations:
//
//   *it      — dereference (return the current element)
//   ++it     — advance to the next element (pre-increment)
//   it != other — inequality comparison
//
// A simple integer range class can provide its own iterator that counts
// from a start value to an end value. This is the foundation for more
// complex custom iterators.
//
// TODO:
//   1. Implement the IntRange::Iterator class:
//      - Constructor that takes an int value
//      - operator*  — return the current value
//      - operator++ (pre-increment) — advance and return *this
//      - operator!= — compare two iterators
//   2. Implement IntRange::begin() and IntRange::end()
//   3. Implement range_sum() — use a range-for loop over an IntRange
//      to sum the values.
//   4. Implement collect_range() — use a range-for loop over an IntRange
//      to collect values into a vector.

#pragma once

#include <vector>
#include <testkit/testkit.h>

// A half-open range [start, stop) of integers.
// Supports range-for iteration.
class IntRange {
    int start_;
    int stop_;

public:
    IntRange(int start, int stop) : start_(start), stop_(stop) {}

    // The iterator type for IntRange.
    class Iterator {
        int current_;

    public:
        // Construct an iterator at the given position.
        explicit Iterator(int value) : current_(value) {}

        // Dereference: return the current integer value.
        inline int operator*() const {
            TODO();
        }

        // Pre-increment: advance to the next integer and return *this.
        inline Iterator& operator++() {
            TODO();
        }

        // Inequality: two iterators are unequal if they point to different values.
        inline bool operator!=(const Iterator& other) const {
            TODO();
        }
    };

    // Return an iterator to the start of the range.
    inline Iterator begin() const {
        TODO();
    }

    // Return an iterator to the end (one past the last element).
    inline Iterator end() const {
        TODO();
    }
};

// Sum all values in the range [start, stop) using a range-for loop.
inline int range_sum(int start, int stop) {
    TODO();
}

// Collect all values in the range [start, stop) into a vector.
inline std::vector<int> collect_range(int start, int stop) {
    TODO();
}
