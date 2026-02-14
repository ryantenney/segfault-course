// Exercise 02: Multiple Type Parameters
//
// PROBLEM:
//   A template can have more than one type parameter. This lets you write
//   functions that work with different input and output types.
//
//   Here you'll write a `convert<To>(From val)` function. The `To` type
//   must be explicitly specified (it cannot be deduced), while `From` is
//   deduced from the argument.
//
// TODO:
//   1. Implement convert<To, From>(From val): use static_cast<To>(val).
//   2. Implement make_pair_of(T a, U b): return a std::pair<T, U>.
//
// WHY:
//   Multiple type parameters let templates bridge between types. The
//   convert pattern (explicit return type, deduced argument type) is
//   common in real code: think std::static_pointer_cast, std::any_cast.

#pragma once

#include <utility>
#include <testkit/testkit.h>

// Convert val from type From to type To using static_cast.
// Usage: convert<double>(42)  =>  42.0
template<typename To, typename From>
To convert(From val) {
    TODO();
}

// Create a std::pair from two values of potentially different types.
template<typename T, typename U>
std::pair<T, U> make_pair_of(T a, U b) {
    TODO();
}
