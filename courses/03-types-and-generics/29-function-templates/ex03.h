// Exercise 03: Non-Type Template Parameter
//
// PROBLEM:
//   Templates can be parameterized not just by types, but by values:
//   integers, enums, pointers. A non-type template parameter is a
//   compile-time constant that becomes part of the type itself.
//
//   `std::array<int, 5>` and `std::array<int, 10>` are different types
//   because the size is a template parameter, not a runtime value.
//
// TODO:
//   Implement the FixedBuffer<N> class template:
//   1. It contains a std::array<int, N> member.
//   2. Implement operator[], size(), fill(), and sum().
//
// WHY:
//   Non-type template parameters let you embed sizes, capacities, and
//   other constants into the type system. The compiler knows the size
//   at compile time, enabling optimizations like stack allocation and
//   loop unrolling.

#pragma once

#include <array>
#include <cstddef>
#include <testkit/testkit.h>

template<std::size_t N>
class FixedBuffer {
    std::array<int, N> data_{};

public:
    // Default constructor: zero-initializes the array (already done above).
    FixedBuffer() = default;

    // Access element at index.
    int& operator[](std::size_t index) {
        TODO();
    }

    const int& operator[](std::size_t index) const {
        TODO();
    }

    // Return the compile-time size of the buffer.
    std::size_t size() const {
        TODO();
    }

    // Fill all elements with the given value.
    void fill(int value) {
        TODO();
    }

    // Return the sum of all elements.
    int sum() const {
        TODO();
    }
};
