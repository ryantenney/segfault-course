// Exercise 02: Reference Collapsing
//
// When references to references arise (through templates or type aliases),
// C++ applies "reference collapsing" rules:
//
//   T& &   => T&      (lvalue ref to lvalue ref => lvalue ref)
//   T& &&  => T&      (rvalue ref to lvalue ref => lvalue ref)
//   T&& &  => T&      (lvalue ref to rvalue ref => lvalue ref)
//   T&& && => T&&     (rvalue ref to rvalue ref => rvalue ref)
//
// The rule is simple: if EITHER reference is an lvalue reference, the result
// is an lvalue reference. Only rvalue ref + rvalue ref gives rvalue ref.
//
// This is why forwarding references work: when you call f(T&& arg) with an
// lvalue of type X, T deduces to X& and T&& collapses to X& && => X&.
//
// TODO:
//   1. Implement collapsed_type_is_lref<T>(): return true if T& (adding an
//      lvalue reference to T) is an lvalue reference. (It always is, but
//      this demonstrates the trait.)
//
//   2. Implement deduce_and_report<T>(T&&): return "T=lref" if T was deduced
//      as an lvalue reference type, "T=nonref" if T is a non-reference type.
//
//   3. Implement apply_collapse<T>(): given a type T (which may already be a
//      reference), return a string describing what T&& collapses to:
//      "lvalue_ref" if std::is_lvalue_reference_v<T&&>, else "rvalue_ref".

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>

// Return true if adding & to T produces an lvalue reference.
template <typename T>
bool collapsed_type_is_lref() {
    TODO();
    // Hint: return std::is_lvalue_reference_v<T&>;
    // (This is always true due to collapsing -- that's the point.)
}

// T is deduced from the argument. Report what T deduced to.
template <typename T>
std::string deduce_and_report(T&&) {
    TODO();
    // Hint: if std::is_lvalue_reference_v<T>, T was deduced as an lref.
    // Return "T=lref" or "T=nonref".
}

// Given T (which may already be a reference type), report what T&& collapses to.
template <typename T>
std::string apply_collapse() {
    TODO();
    // Hint: check std::is_lvalue_reference_v<T&&>
    // Return "lvalue_ref" or "rvalue_ref".
}
