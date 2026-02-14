// Exercise 04: Constrained Class Template
//
// PROBLEM:
//   Concepts can constrain class templates, not just functions.  A
//   constrained class template only compiles when instantiated with
//   types that satisfy the concept.
//
// TODO:
//   1. Fix the `Comparable` concept below.  Currently it accepts ALL
//      types.  Replace `true` with a requires expression that checks:
//      - { a < b }  -> std::convertible_to<bool>
//      - { a == b } -> std::convertible_to<bool>
//
//   2. Constrain the SortedContainer class template to only accept
//      types that satisfy Comparable.  Change `template<typename T>` to
//      `template<Comparable T>`.
//
//   3. Implement insert() -- add the value and keep the container sorted.
//      Hint: use std::lower_bound from <algorithm> to find the right
//      position, then use data_.insert(it, value).
//
//   4. Implement contains() -- return true if the value exists.
//      Hint: use std::binary_search from <algorithm>.
//
//   5. Implement size() and at().
//
// WHY:
//   Constraining class templates catches misuse at the point of
//   instantiation, not deep inside an unreadable error trace.

#pragma once

#include <testkit/testkit.h>
#include <algorithm>
#include <concepts>
#include <vector>

// Fix this concept: replace `true` with the proper requirements.
template<typename T>
concept Comparable = true;  // TODO: add requires(T a, T b) { ... }

// A container that keeps its elements sorted.
// TODO: Constrain T with the Comparable concept.
template<typename T>
class SortedContainer {
    std::vector<T> data_;

public:
    // Insert a value in sorted order.
    void insert(const T& value) {
        TODO();
    }

    // Return true if the value exists in the container.
    bool contains(const T& value) const {
        TODO();
    }

    // Return the number of elements.
    std::size_t size() const {
        TODO();
    }

    // Return the element at index i.
    const T& at(std::size_t i) const {
        TODO();
    }
};
