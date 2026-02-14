// Exercise 07: Move-Only Type
//
// PROBLEM:
//   A move-only type can be transferred but not duplicated. This models
//   exclusive ownership of a resource: exactly one object owns it at any
//   time. Examples in the standard library: unique_ptr, thread, fstream.
//
//   You build a move-only type by:
//     - Deleting the copy constructor and copy assignment operator.
//     - Implementing the move constructor and move assignment operator.
//
// TODO:
//   The copy constructor and copy assignment are already deleted for you.
//   1. Implement the move constructor: transfer ownership, mark source invalid.
//      (Add noexcept when done.)
//   2. Implement the move assignment operator: release current resource, transfer
//      ownership, mark source invalid. (Add noexcept when done.)
//   3. Implement make_handles: create a vector of UniqueHandle objects.
//
// WHY:
//   Move-only types enforce single ownership at compile time. You can store
//   them in standard containers (vector, map) and return them from functions,
//   but you cannot accidentally create two owners of the same resource.

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <testkit/testkit.h>

class UniqueHandle {
    int id_;
    std::string label_;
    bool valid_;

public:
    UniqueHandle(int id, std::string label)
        : id_(id), label_(std::move(label)), valid_(true) {}

    ~UniqueHandle() = default;

    // Delete copy operations.
    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    // Move constructor: transfer ownership from other.
    // TODO: Add noexcept to this function when you implement it.
    UniqueHandle(UniqueHandle&& other) {
        TODO();
    }

    // Move assignment: release current, transfer from other.
    // TODO: Add noexcept to this function when you implement it.
    UniqueHandle& operator=(UniqueHandle&& other) {
        TODO();
    }

    int id() const { return id_; }
    const std::string& label() const { return label_; }
    bool valid() const { return valid_; }
};

// Create a vector of `count` UniqueHandle objects with ids 0 through count-1.
// Each handle should have label "handle-N" where N is the id.
inline std::vector<UniqueHandle> make_handles(std::size_t count) {
    TODO();
}
