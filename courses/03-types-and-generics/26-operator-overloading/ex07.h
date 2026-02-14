// Exercise 07: Subscript Operator
//
// operator[] provides array-like access to elements within your class.
// You typically need two overloads:
//
//   T&       operator[](size_t index);        // non-const: allows modification
//   const T& operator[](size_t index) const;  // const: read-only access
//
// The const overload is called when the object is const (or accessed through
// a const reference). The non-const overload is called otherwise and allows
// the caller to modify the element.
//
// TODO:
//   1. Implement the non-const operator[] for FixedArray.
//      Return a reference to the element at the given index.
//   2. Implement the const operator[] for FixedArray.
//      Return a const reference to the element at the given index.
//   3. Implement size() to return the number of elements.

#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>
#include <testkit/testkit.h>

class FixedArray {
    static constexpr std::size_t N = 5;
    std::array<int, N> data_{};

public:
    // Return the number of elements.
    std::size_t size() const {
        TODO();
    }

    // Return a reference to the element at `index`.
    // Throw std::out_of_range if index >= N.
    int& operator[](std::size_t index) {
        TODO();
    }

    // Return a const reference to the element at `index`.
    // Throw std::out_of_range if index >= N.
    const int& operator[](std::size_t index) const {
        TODO();
    }
};
