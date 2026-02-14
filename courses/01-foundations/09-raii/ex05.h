// Exercise 05: RAII for Dynamic Allocation
//
// PROBLEM:
//   Raw new/delete is error-prone. If you forget delete, or if an
//   exception occurs before delete, you leak memory. An RAII wrapper
//   ensures delete always runs.
//
// TODO:
//   Implement IntBox — a simplified unique_ptr<int>:
//   - Constructor: allocate an int with new and store the initial value
//   - Destructor: delete the pointer
//   - get(): return the raw pointer
//   - value(): return the current int value
//   - set(): change the stored int value
//
// WHY:
//   This is a simplified version of std::unique_ptr. In real code you
//   should always use unique_ptr, but building one yourself reveals
//   why RAII is the foundation of memory safety in C++.

#pragma once
#include <testkit/testkit.h>

// Tracks allocations for testing purposes.
struct AllocTracker {
    static inline int active_allocations = 0;
};

class IntBox {
    // TODO: Add an int* member
public:
    // Allocate a new int with the given initial value.
    // Increment AllocTracker::active_allocations.
    explicit IntBox(int value) {
        TODO();
    }

    // Delete the owned int.
    // Decrement AllocTracker::active_allocations.
    ~IntBox() {
        // TODO: delete the pointer, decrement active_allocations
    }

    // Return the raw pointer.
    int* get() const {
        TODO();
    }

    // Return the current value.
    int value() const {
        TODO();
    }

    // Set a new value.
    void set(int v) {
        TODO();
    }

    // Non-copyable
    IntBox(const IntBox&) = delete;
    IntBox& operator=(const IntBox&) = delete;
};
