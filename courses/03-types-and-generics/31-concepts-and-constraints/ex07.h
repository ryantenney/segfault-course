// Exercise 07: Subsumption Ordering
//
// PROBLEM:
//   When multiple constrained overloads match, the compiler uses
//   "subsumption ordering" to pick the most constrained one.  A concept
//   A "subsumes" concept B if A's constraints include all of B's (and
//   possibly more).  The compiler always picks the most constrained match.
//
//   For subsumption to work, the refined concept must be defined IN TERMS
//   OF the general concept using &&.
//
// TODO:
//   1. Fix the `Ordered` concept -- replace `true` with a requires
//      expression that checks { a < b } -> std::convertible_to<bool>.
//
//   2. Fix the `Named` concept -- replace `true` with a requires
//      expression that checks { a.name() } -> std::convertible_to<std::string>.
//
//   3. Fix `OrderedAndNamed` -- replace `true` with `Ordered<T> && Named<T>`.
//
//   4. Add the Ordered constraint to the first `identify` overload.
//      Return "ordered".
//
//   5. Uncomment and add the OrderedAndNamed constraint to the second
//      `identify` overload.
//      Return "ordered+named: " + value.name().
//
//      The compiler will pick the OrderedAndNamed overload when both match,
//      because it's more constrained (subsumes Ordered).
//
// WHY:
//   Subsumption is what makes concept-based overloading work without
//   ambiguity.  Without it, having both Ordered and OrderedAndNamed
//   overloads would be an error.

#pragma once

#include <testkit/testkit.h>
#include <concepts>
#include <string>

// Fix these concepts: replace `true` with the proper requirements.
template<typename T>
concept Ordered = true;  // TODO: requires(T a, T b) { { a < b } -> std::convertible_to<bool>; }

template<typename T>
concept Named = true;  // TODO: requires(T a) { { a.name() } -> std::convertible_to<std::string>; }

template<typename T>
concept OrderedAndNamed = true;  // TODO: Ordered<T> && Named<T>

// Overload for types that are Ordered but not necessarily Named.
// TODO: Constrain with Ordered. Return "ordered".
template<typename T>
std::string identify(const T& value) {
    TODO();
}

// TODO: Uncomment and constrain with OrderedAndNamed.
// Return: "ordered+named: " + value.name()
//
// template<OrderedAndNamed T>
// std::string identify(const T& value) {
//     TODO();
// }
