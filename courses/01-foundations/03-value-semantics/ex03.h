// Exercise 03: Const-Qualify a Method
//
// CONTEXT:
//   A method marked `const` promises not to modify the object's state.
//   This allows it to be called on const objects and through const
//   references — which is critical since `const T&` is the standard
//   parameter type for read-only access.
//
//   The Counter class below has getter methods correctly marked as
//   `const`. Without that qualifier, you couldn't call get_count()
//   or get_name() on a `const Counter`.
//
// TODO:
//   Implement get_count() and get_name().
//
// THINK ABOUT:
//   Try removing the `const` keyword from get_count() and observe the
//   compiler error when the test creates a `const Counter` and calls it.

#pragma once

#include <testkit/testkit.h>
#include <string>

class Counter {
    std::string name_;
    int count_;

public:
    Counter(const std::string& name, int initial)
        : name_(name), count_(initial) {}

    void increment() { ++count_; }

    // const — this method does not modify the object
    int get_count() const {
        TODO();
    }

    // const — this method does not modify the object
    std::string get_name() const {
        TODO();
    }
};
