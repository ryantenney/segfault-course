// Exercise 01: static_assert with Type Traits
//
// The <type_traits> header provides compile-time predicates about types:
// std::is_integral_v<T>, std::is_floating_point_v<T>, std::is_arithmetic_v<T>,
// std::is_same_v<T, U>, and many more.
//
// static_assert(condition, "message") fires at compile time if the condition
// is false. Combining static_assert with type traits lets you reject invalid
// template instantiations with a clear error message -- far better than the
// pages of template errors you'd get otherwise.
//
// TODO:
//   1. In numeric_add(), add a static_assert that T is arithmetic
//      (std::is_arithmetic_v<T>). Then return a + b.
//   2. In safe_cast(), add a static_assert that both From and To are
//      integral types (std::is_integral_v). Then return static_cast<To>(v).
//   3. In require_same(), add a static_assert that T and U are the same
//      type (std::is_same_v<T, U>). Then return the value.

#pragma once

#include <testkit/testkit.h>
#include <type_traits>

// Returns a + b, but only compiles if T is an arithmetic type.
template <typename T>
T numeric_add(T a, T b) {
    TODO();
}

// Casts v from type From to type To, but only compiles if both are integral.
template <typename To, typename From>
To safe_cast(From v) {
    TODO();
}

// Returns the value unchanged, but only compiles if T and U are the same type.
template <typename T, typename U>
T require_same(U value) {
    TODO();
}
