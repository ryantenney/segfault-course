// Exercise 04: Forward to Constructor
//
// A common use of perfect forwarding is wrapping object construction. You
// want to forward arguments through a wrapper function directly into a
// constructor, avoiding any intermediate copies or moves.
//
// This pattern is the foundation for std::make_unique, std::make_shared,
// and container emplace methods.
//
// TODO:
//   1. Implement construct_in_place<T>(Args&&... args):
//      Create and return a T by perfectly forwarding the constructor args.
//
//   2. Implement construct_pair(a, b):
//      Return a NamedPair by forwarding `a` into the `first` field and
//      `b` into the `second` field using the NamedPair constructor.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>

// Tracker to detect copy/move behavior.
struct Widget {
    std::string name;
    int value;
    bool was_moved = false;

    Widget(std::string n, int v) : name(std::move(n)), value(v) {}

    Widget(const Widget& other)
        : name(other.name), value(other.value), was_moved(false) {}

    Widget(Widget&& other) noexcept
        : name(std::move(other.name)), value(other.value), was_moved(true) {
        other.name = "(moved)";
        other.value = 0;
    }

    Widget& operator=(const Widget&) = default;
    Widget& operator=(Widget&&) = default;
};

struct NamedPair {
    std::string first;
    std::string second;

    NamedPair(std::string a, std::string b)
        : first(std::move(a)), second(std::move(b)) {}
};

// Construct and return a T by perfectly forwarding constructor arguments.
template <typename T, typename... Args>
T construct_in_place(Args&&... args) {
    TODO();
    // Hint: return T(std::forward<Args>(args)...);
}

// Construct a NamedPair by forwarding a and b to its constructor.
template <typename A, typename B>
NamedPair construct_pair(A&& a, B&& b) {
    TODO();
    // Hint: return NamedPair(std::forward<A>(a), std::forward<B>(b));
}
