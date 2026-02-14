// Exercise 06: Copy-and-Swap Idiom
//
// PROBLEM:
//   Writing a correct copy assignment operator is tricky: you need to handle
//   self-assignment, free old resources, allocate new resources, and be
//   exception-safe. The copy-and-swap idiom solves all of this elegantly:
//
//     1. Take the parameter by value (which invokes the copy constructor).
//     2. Swap the copy's contents with *this.
//     3. The old data is now in the temporary and gets destroyed automatically.
//
//   This gives you strong exception safety for free: if the copy fails
//   (throws), *this is untouched.
//
// TODO:
//   1. Implement the swap function: swap all members between *this and other.
//      (Add noexcept when done.)
//   2. Implement the copy assignment operator using the copy-and-swap idiom:
//      take the parameter by value, swap with *this, return *this.
//   3. Implement the copy constructor: allocate and deep-copy.
//   4. Implement the move constructor: steal resources, null out source.
//      (Add noexcept when done.)
//
// WHY:
//   Copy-and-swap is a battle-tested pattern. It automatically handles
//   self-assignment, provides strong exception safety, and reduces
//   duplication between copy constructor and copy assignment.

#pragma once

#include <cstddef>
#include <algorithm>
#include <testkit/testkit.h>

class SwapBuffer {
    int* data_;
    std::size_t size_;

public:
    // Construct with given size, zero-initialized.
    SwapBuffer(std::size_t size)
        : data_(new int[size]()), size_(size) {}

    // Destructor: provided -- do NOT modify.
    ~SwapBuffer() {
        delete[] data_;
    }

    // Swap the contents of *this with other.
    // TODO: Add noexcept to this function when you implement it.
    void swap(SwapBuffer& other) {
        TODO();
    }

    // Copy constructor: deep-copy from other.
    SwapBuffer(const SwapBuffer& other) {
        TODO();
    }

    // Move constructor: steal resources from other.
    // TODO: Add noexcept to this function when you implement it.
    SwapBuffer(SwapBuffer&& other) {
        TODO();
    }

    // Copy assignment using copy-and-swap idiom.
    // Note: parameter is taken BY VALUE (this invokes the copy constructor).
    SwapBuffer& operator=(SwapBuffer other) {
        TODO();
    }

    int& operator[](std::size_t index) { return data_[index]; }
    const int& operator[](std::size_t index) const { return data_[index]; }
    std::size_t size() const { return size_; }
    const int* data() const { return data_; }
};

// Free function swap (delegates to member swap).
// TODO: Add noexcept to this function when you implement it.
inline void swap(SwapBuffer& a, SwapBuffer& b) {
    a.swap(b);
}
