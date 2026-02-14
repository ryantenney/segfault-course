// Exercise 01: Spot the Bug (Rule of Three Violation)
//
// PROBLEM:
//   The IntArray class below manages a dynamically allocated array. It has a
//   destructor that frees the memory, but no copy constructor or copy
//   assignment operator. This is a classic Rule of Three violation.
//
//   When you copy an IntArray, the default (shallow) copy duplicates the
//   raw pointer. Both objects then think they own the same memory. When the
//   first one destructs, it frees the array. The second object now has a
//   dangling pointer -- using it is undefined behavior, and its destructor
//   will double-free.
//
// TODO:
//   1. Implement the copy constructor: allocate new memory and copy elements.
//   2. Implement the copy assignment operator: handle self-assignment, free
//      old memory, allocate new memory, and copy elements.
//
// WHY:
//   If a class needs a custom destructor, it almost certainly needs a custom
//   copy constructor and copy assignment operator too. This is the Rule of
//   Three. Forgetting any one of the three is a common source of crashes.

#pragma once

#include <cstddef>
#include <algorithm>
#include <testkit/testkit.h>

class IntArray {
    int* data_;
    std::size_t size_;

public:
    // Construct with a given size, all elements initialized to zero.
    IntArray(std::size_t size)
        : data_(new int[size]()), size_(size) {}

    // Destructor: frees the dynamic array.
    ~IntArray() {
        delete[] data_;
    }

    // Copy constructor: deep-copy the array from other.
    IntArray(const IntArray& other) {
        TODO();
    }

    // Copy assignment operator: deep-copy with self-assignment safety.
    IntArray& operator=(const IntArray& other) {
        TODO();
    }

    int& operator[](std::size_t index) { return data_[index]; }
    const int& operator[](std::size_t index) const { return data_[index]; }
    std::size_t size() const { return size_; }
    const int* data() const { return data_; }
};
