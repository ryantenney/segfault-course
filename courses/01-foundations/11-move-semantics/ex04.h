// Exercise 04: Move Assignment Operator
//
// Move assignment transfers resources from one existing object to another.
// It must handle the case where the destination already owns resources
// (they need to be cleaned up or swapped).
//
// A self-assignment guard (`if (this != &other)`) is good practice,
// though for unique_ptr it's technically safe without one.
//
// Signature: ClassName& operator=(ClassName&& other) noexcept
//
// TODO:
//   Implement the move assignment operator for Storage.

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <testkit/testkit.h>

class Storage {
    std::unique_ptr<std::string[]> items_;
    std::size_t capacity_;

public:
    explicit Storage(std::size_t capacity)
        : items_(std::make_unique<std::string[]>(capacity)),
          capacity_(capacity) {}

    // Copy is deleted.
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    // Move constructor -- provided for you.
    Storage(Storage&& other) noexcept
        : items_(std::move(other.items_)),
          capacity_(other.capacity_) {
        other.capacity_ = 0;
    }

    // Move assignment operator -- TODO: implement this.
    // 1. Guard against self-assignment.
    // 2. Transfer items_ and capacity_ from other.
    // 3. Leave other in an empty state.
    // 4. Return *this.
    // Best practice: move assignment should be noexcept.
    Storage& operator=(Storage&& other);

    std::size_t capacity() const { return capacity_; }
    bool empty() const { return capacity_ == 0; }

    void set(std::size_t index, const std::string& value) {
        items_[index] = value;
    }

    const std::string& get(std::size_t index) const {
        return items_[index];
    }
};

// TODO: Implement the move assignment operator.
inline Storage& Storage::operator=(Storage&& other) {
    TODO();
}
