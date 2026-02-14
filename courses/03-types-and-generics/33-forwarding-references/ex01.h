// Exercise 01: Forwarding Reference vs Rvalue Reference
//
// `T&&` has two completely different meanings depending on context:
//
//   1. When T is a deduced template parameter:  T&&  is a FORWARDING reference
//      (also called a universal reference). It can bind to lvalues AND rvalues.
//
//   2. When the type is concrete (not deduced):  int&&  is an RVALUE reference.
//      It can only bind to rvalues.
//
// The key distinction: if `T` is deduced by the compiler from the argument,
// then `T&&` is a forwarding reference. If the type is fully spelled out,
// it's an rvalue reference.
//
// TODO:
//   1. Implement is_forwarding_ref_call(): call the provided function template
//      `identify` with an lvalue (a named variable). If it's truly a forwarding
//      reference, this will compile. Return the result.
//
//   2. Implement takes_rvalue_only(): call the provided function `consume`
//      with an rvalue (use std::move). Return the result.
//
//   3. Implement classify_argument(): given a deduced T&&, return "lvalue" if
//      T deduces to an lvalue reference type, or "rvalue" otherwise.
//      Hint: use std::is_lvalue_reference_v<T>.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>
#include <utility>

// This function template takes a forwarding reference.
// It returns "lvalue" if called with an lvalue, "rvalue" if called with an rvalue.
template <typename T>
std::string identify(T&&) {
    if constexpr (std::is_lvalue_reference_v<T>) {
        return "lvalue";
    } else {
        return "rvalue";
    }
}

// This function takes a concrete rvalue reference (NOT a forwarding ref).
inline std::string consume(std::string&& s) {
    return "consumed: " + s;
}

// Call identify() with an lvalue string and return the result.
inline std::string is_forwarding_ref_call() {
    TODO();
    // Hint: create a local std::string variable, pass it to identify().
}

// Call consume() with an rvalue and return the result.
inline std::string takes_rvalue_only(std::string s) {
    TODO();
    // Hint: use std::move(s) to turn the lvalue into an rvalue.
}

// Classify whether the argument was passed as an lvalue or rvalue.
// T&& is a forwarding reference here because T is deduced.
template <typename T>
std::string classify_argument(T&&) {
    TODO();
    // Hint: return "lvalue" if std::is_lvalue_reference_v<T>, else "rvalue".
}
