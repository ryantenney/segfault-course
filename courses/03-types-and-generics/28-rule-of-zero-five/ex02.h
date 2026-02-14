// Exercise 02: Rule of Zero
//
// PROBLEM:
//   The class from Exercise 1 needed custom copy/destroy logic because it
//   managed raw memory. But if we use smart pointers and standard containers,
//   the compiler-generated special members do the right thing automatically.
//
//   This is the Rule of Zero: prefer to use member types whose default
//   operations do the right thing, so your class doesn't need any custom
//   special members at all.
//
// TODO:
//   Refactor ManagedArray to use std::vector<int> instead of raw int*.
//   - Replace the raw pointer + size with a std::vector<int> member.
//   - Remove the destructor (the vector cleans up automatically).
//   - Implement the constructor, operator[], size(), and data() methods
//     using vector operations.
//   - Do NOT declare any copy/move/destructor -- let the compiler generate them.
//
// WHY:
//   The Rule of Zero is the preferred approach in modern C++. By composing
//   your class from well-behaved member types (vector, string, unique_ptr),
//   you get correct copy, move, and destruction for free.

#pragma once

#include <cstddef>
#include <vector>
#include <testkit/testkit.h>

class ManagedArray {
    // TODO: Replace with a std::vector<int> member.
    //       Remove the destructor. Remove all special members.
    //       The compiler-generated defaults will be correct.

public:
    // Construct with a given size, all elements initialized to zero.
    ManagedArray(std::size_t size) {
        TODO();
    }

    int& operator[](std::size_t index) {
        TODO();
    }

    const int& operator[](std::size_t index) const {
        TODO();
    }

    std::size_t size() const {
        TODO();
    }

    const int* data() const {
        TODO();
    }
};
