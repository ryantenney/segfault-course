// Exercise 06: Move-Only Type
//
// A move-only type can be moved but not copied. This is the natural model
// for resources with unique ownership (file handles, network sockets,
// GPU buffers, etc.). std::unique_ptr is the canonical move-only type.
//
// To make a class move-only:
//   1. Delete the copy constructor and copy assignment operator.
//   2. Define (or default) the move constructor and move assignment operator.
//
// Move-only types can be stored in std::vector -- the vector uses move
// operations internally when it resizes.
//
// TODO:
//   Implement the UniqueHandle class and the helper functions.

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <testkit/testkit.h>

class UniqueHandle {
    std::string name_;
    int id_;
    bool valid_;

public:
    // Construct a valid handle.
    UniqueHandle(std::string name, int id);

    // Deleted copy operations.
    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    // Move operations -- TODO: implement these.
    // Best practice: move operations should be noexcept.
    UniqueHandle(UniqueHandle&& other);
    UniqueHandle& operator=(UniqueHandle&& other);

    const std::string& name() const { return name_; }
    int id() const { return id_; }
    bool valid() const { return valid_; }
};

// TODO: Implement the constructor.
inline UniqueHandle::UniqueHandle(std::string name, int id)
    : name_(std::move(name)), id_(id), valid_(true) {}

// TODO: Implement the move constructor.
// Transfer all fields from other, then mark other as invalid (valid_ = false)
// and clear its name.
inline UniqueHandle::UniqueHandle(UniqueHandle&& other)
    : name_(), id_(0), valid_(false)
{
    TODO();
}

// TODO: Implement move assignment.
inline UniqueHandle& UniqueHandle::operator=(UniqueHandle&& other) {
    TODO();
}

// Create a vector of UniqueHandles. Since they are move-only, you must
// use std::move or emplace_back.
inline std::vector<UniqueHandle> make_handles(int count) {
    TODO();
}
