// Exercise 06: Static Member Variable
//
// PROBLEM:
//   You want to track how many Widget instances are currently alive.
//   A static member variable belongs to the class, not to any instance
//   — perfect for a shared counter.
//
// TODO:
//   1. Implement instance_count() — returns the current value of count_
//   2. Implement reset_count() — resets count_ to 0 (useful for tests)
//   3. Implement id() — returns this widget's unique ID
//
//   The constructor and destructor are already provided. They increment
//   and decrement count_ respectively.
//
// WHY:
//   Static members are shared across all instances. They're useful for
//   counters, caches, and singleton-like patterns. Because they exist
//   at class scope, they're initialized once and persist for the
//   program's lifetime.

#pragma once

#include <testkit/testkit.h>

class Widget {
private:
    int id_;
    static inline int count_ = 0;
    static inline int next_id_ = 0;

public:
    // Constructor: increments the instance count and assigns a unique ID.
    // (Provided — do not modify.)
    Widget() : id_(next_id_++) {
        ++count_;
    }

    // Destructor: decrements the instance count.
    // (Provided — do not modify.)
    ~Widget() {
        --count_;
    }

    // Disallow copying to keep the count accurate.
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    // Allow moves — transfer ownership without changing count.
    Widget(Widget&& other) : id_(other.id_) {
        other.id_ = -1;  // Mark moved-from
        // No count change: one object created, one will be destroyed
    }

    Widget& operator=(Widget&& other) {
        if (this != &other) {
            id_ = other.id_;
            other.id_ = -1;
        }
        return *this;
    }

    // Returns the number of currently alive Widget instances.
    static int instance_count() {
        TODO();
    }

    // Resets the instance count and next ID to zero.
    // Useful for test isolation.
    static void reset_count() {
        TODO();
    }

    // Returns this widget's unique ID.
    int id() const {
        TODO();
    }
};
