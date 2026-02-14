// Exercise 05: Default Constructor Control
//
// PROBLEM:
//   The compiler generates a default constructor only if you declare
//   NO constructors at all. Once you add any constructor, the implicit
//   default constructor disappears. You can bring it back with `= default`.
//
// TODO:
//   1. The Timestamp class has a parameterized constructor, so it lost
//      its default constructor. Add `= default` to restore it.
//   2. Implement the parameterized constructor and getters.
//   3. The NonDefaultable class should NOT have a default constructor.
//      Add `= delete` to explicitly forbid it.
//   4. Implement the make_timestamp() and make_pair() functions.
//
// WHY:
//   Understanding when the compiler generates (or suppresses) special
//   member functions is essential in C++. `= default` and `= delete`
//   give you explicit control: default says "generate it," delete says
//   "forbid it."

#pragma once

#include <testkit/testkit.h>
#include <utility>

class Timestamp {
private:
    int seconds_;
    int nanoseconds_;

public:
    // TODO: Declare a defaulted default constructor.
    // It should initialize seconds_ to 0 and nanoseconds_ to 0.
    // Hint: Use in-class member initializers for the defaults,
    // then declare: Timestamp() = default;

    // Parameterized constructor.
    Timestamp(int seconds, int nanoseconds)
        : seconds_(seconds), nanoseconds_(nanoseconds) {}

    int seconds() const {
        TODO();
    }

    int nanoseconds() const {
        TODO();
    }
};

class NonDefaultable {
private:
    int value_;

public:
    // TODO: Delete the default constructor to prevent default construction.
    // NonDefaultable() = delete;

    explicit NonDefaultable(int v) : value_(v) {}

    int value() const {
        TODO();
    }
};

// Creates a default-constructed Timestamp (epoch: 0 seconds, 0 nanoseconds).
inline Timestamp make_epoch() {
    TODO();
}

// Creates a Timestamp from the given values.
inline Timestamp make_timestamp(int sec, int nsec) {
    TODO();
}

// Returns a pair of NonDefaultable objects.
inline std::pair<NonDefaultable, NonDefaultable> make_pair(int a, int b) {
    TODO();
}
