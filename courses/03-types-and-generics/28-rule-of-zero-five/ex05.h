// Exercise 05: Rule of Five
//
// PROBLEM:
//   When a class manages a raw resource (here, a dynamically allocated int
//   array), you need to implement all five special members:
//     1. Destructor
//     2. Copy constructor
//     3. Copy assignment operator
//     4. Move constructor
//     5. Move assignment operator
//
//   The destructor is provided for you. Implement the other four.
//
// TODO:
//   1. Implement the copy constructor: allocate new memory, copy elements.
//   2. Implement the move constructor: steal the pointer and size, null out
//      the source. (Add noexcept when done.)
//   3. Implement the copy assignment operator: free old memory, allocate new,
//      copy elements. Handle self-assignment.
//   4. Implement the move assignment operator: free old memory, steal from
//      source, null out source. Handle self-assignment. (Add noexcept when done.)
//
// WHY:
//   The Rule of Five ensures your class is safe to copy, move, and destroy.
//   Missing any member leads to double-free, memory leak, or use-after-free.

#pragma once

#include <cstddef>
#include <algorithm>
#include <testkit/testkit.h>

class DynamicBuffer {
    int* data_;
    std::size_t size_;

public:
    // Construct with given size, zero-initialized.
    DynamicBuffer(std::size_t size)
        : data_(new int[size]()), size_(size) {}

    // Destructor: provided for you -- do NOT modify.
    ~DynamicBuffer() {
        delete[] data_;
    }

    // Copy constructor: deep-copy from other.
    DynamicBuffer(const DynamicBuffer& other) {
        TODO();
    }

    // Move constructor: steal resources from other.
    // TODO: Add noexcept to this function when you implement it.
    DynamicBuffer(DynamicBuffer&& other) {
        TODO();
    }

    // Copy assignment operator: deep-copy with self-assignment safety.
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        TODO();
    }

    // Move assignment operator: steal resources from other.
    // TODO: Add noexcept to this function when you implement it.
    DynamicBuffer& operator=(DynamicBuffer&& other) {
        TODO();
    }

    int& operator[](std::size_t index) { return data_[index]; }
    const int& operator[](std::size_t index) const { return data_[index]; }
    std::size_t size() const { return size_; }
    const int* data() const { return data_; }
    int* data() { return data_; }
};
