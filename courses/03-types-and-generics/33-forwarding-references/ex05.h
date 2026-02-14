// Exercise 05: Emplace with Forwarding
//
// Containers like std::vector have emplace_back() which constructs an
// element in place by forwarding arguments directly to the constructor.
// This avoids creating a temporary and then moving it into the container.
//
// In this exercise, you'll build a simplified container with an emplace_back
// method that uses perfect forwarding.
//
// TODO:
//   Implement MiniVec::emplace_back(Args&&... args):
//   1. Construct a T from the forwarded arguments.
//   2. Push it into the internal storage vector.
//   Hint: storage_.push_back(T(std::forward<Args>(args)...));
//   Or even better: storage_.emplace_back(std::forward<Args>(args)...);

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>
#include <vector>

// A simple wrapper around std::vector with a custom emplace_back.
template <typename T>
class MiniVec {
    std::vector<T> storage_;

public:
    // Construct a T in place from forwarded arguments.
    template <typename... Args>
    void emplace_back(Args&&... args) {
        TODO();
    }

    std::size_t size() const { return storage_.size(); }
    bool empty() const { return storage_.empty(); }
    const T& operator[](std::size_t i) const { return storage_[i]; }
    const T& back() const { return storage_.back(); }
};

// A type that tracks how it was constructed.
struct Entry {
    std::string name;
    int id;
    bool constructed_from_args = false;
    bool was_copied = false;
    bool was_moved = false;

    Entry(std::string n, int i)
        : name(std::move(n)), id(i), constructed_from_args(true) {}

    Entry(const Entry& other)
        : name(other.name), id(other.id),
          constructed_from_args(false), was_copied(true) {}

    Entry(Entry&& other) noexcept
        : name(std::move(other.name)), id(other.id),
          constructed_from_args(false), was_moved(true) {
        other.name = "(moved)";
        other.id = -1;
    }

    Entry& operator=(const Entry&) = default;
    Entry& operator=(Entry&&) = default;
};
