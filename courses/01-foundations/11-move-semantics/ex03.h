// Exercise 03: Write a Move Constructor
//
// A move constructor transfers resources from a temporary (or explicitly moved)
// object into a new object. For a class that owns a unique_ptr, the move
// constructor should std::move the unique_ptr member.
//
// Signature: ClassName(ClassName&& other) noexcept
//
// After the move, `other` should be in a valid but empty state (its unique_ptr
// is null, its size is 0, etc.).
//
// TODO:
//   Implement the move constructor for Buffer. The copy constructor is deleted
//   because Buffer owns a unique_ptr (which is non-copyable).

#pragma once

#include <cstddef>
#include <memory>
#include <testkit/testkit.h>

class Buffer {
    std::unique_ptr<int[]> data_;
    std::size_t size_;

public:
    // Normal constructor: allocates an array of `size` ints, all zero.
    explicit Buffer(std::size_t size)
        : data_(std::make_unique<int[]>(size)), size_(size) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    // Copy is deleted because unique_ptr is non-copyable.
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // Move constructor -- TODO: implement this.
    // Transfer data_ and size_ from other, leaving other empty.
    // Best practice: move constructors should be noexcept.
    Buffer(Buffer&& other);

    // Move assignment is defaulted for simplicity in this exercise.
    Buffer& operator=(Buffer&&) noexcept = default;

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    int& operator[](std::size_t i) { return data_[i]; }
    const int& operator[](std::size_t i) const { return data_[i]; }

    // Returns true if the buffer owns data.
    bool has_data() const { return data_ != nullptr; }
};

// TODO: Implement the move constructor.
// Hint: use std::move on other.data_ and copy other.size_, then set
//       other.size_ = 0.
inline Buffer::Buffer(Buffer&& other)
    : data_(nullptr), size_(0)
{
    TODO();
}
